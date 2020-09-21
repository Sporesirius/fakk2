#include "cmdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include "mss.h"
#include "scriplib.h"
#include "mathlib.h"
#include "qfiles.h"

#define VERSION "1.0"

#define byte unsigned char

#define LIP_SYNC_HZ  20

#define MAX_STRING_LENGTH 128

typedef struct
{
	byte *data;
	int length;
} sound_file_info_t;

typedef struct
   {
   int inuse;
   char filename[ MAX_STRING_LENGTH ];
   } pakfile_t;

pakfile_t pakfiles[ MAX_FILES_IN_PACK ];

int quiet = false;
int force = false;
int timeonly = false;
char filename[256];
char basedir[1024];
char scriptfile[1024];
int num_files;
FILE *timeonly_fileptr = NULL;

int read_file(char *filename, sound_file_info_t *sound_file_info);
void convert_to_lip(char *filename);
S32 AILCALLBACK asi_callback(U32 state, U32 value);
void save_lip_sync_file(char *filename, int *averaged_samples, int number_of_averaged_samples, float sound_length);
void Exclude( const char * wild, qboolean recursive );
void Include( const char * wild, qboolean recursive );
qboolean ProcessScript( char * filename );
char * FixArgs(char *arg);
void IncludeFile ( char * filename, char * name );
void ExcludeFile ( char * filename, char * name );
void ParseArguments(int argc, char* argv[]);



int main(int argc, char* argv[])
{
	int i;

	printf ("\nLipsync "VERSION" copyright (c) 1999 Ritual Entertainment\n\n");

	//printf("NOTE: Only works on NT right now\n");

	// Initialize everything

	ParseArguments(argc, argv);

	AIL_startup();

   if ( timeonly )
      {
      timeonly_fileptr = fopen( "out.txt", "wt" );
      }

	strlwr(filename);

	if (strstr(filename, ".ls"))
	{
		strcpy(scriptfile, filename);

		// get the current directory

		_getcwd(basedir,1024);

		memset( pakfiles, 0, sizeof( pakfiles ) );
		num_files = 0;

		// Process the list file

		if (ProcessScript(scriptfile))
		{
			// Convert each file specified

			for( i = 0; i < num_files; i++ )
			{
				if ( !pakfiles[ i ].inuse )
					continue;

				if (!force && !timeonly)
				{
					int srctime, desttime;
					char dst_filename[256];

					// Only convert new files or ones that have been changed

					strncpy(dst_filename, pakfiles[ i ].filename, strlen(pakfiles[ i ].filename) - 4);
					dst_filename[strlen(pakfiles[ i ].filename) - 4] = 0;
					strcat(dst_filename, ".lip");

					srctime  = FileTime(pakfiles[ i ].filename);
					desttime = FileTime( dst_filename );

					if ( srctime < desttime )
					{
						printf("Skipping   ...%s\n", pakfiles[ i ].filename);
						continue;
					}
				}

				// Convert the file

				convert_to_lip(pakfiles[ i ].filename);
			}
		}
	}
	else
	{
		// Convert the file

		convert_to_lip(filename);
	}

	AIL_shutdown();

   if ( timeonly )
      {
      fclose( timeonly_fileptr );
      }


	return 0;
}


void convert_to_lip(char *filename)
{
	sound_file_info_t sound_file_info;
	int file_type;
	byte *wave_data;
	byte *final_wave_data;
	unsigned long wave_length;
	unsigned long final_wave_length;
	AILSOUNDINFO adpcm_info;
	//AILSOUNDINFO wave_info;
	int number_of_samples;
	int convert = true;
	int i;
	int sample;
	int sample_total;
	int samples_to_add;
	int samples_added;
	//char *char_ptr;
	short *short_ptr;
	int number_of_averaged_samples;
	int *averaged_samples = NULL;
	float sound_length;
	AILMIXINFO mix;
	unsigned long outsize;
	int highest_value;
	float multiplier;


	if (!quiet)
		printf("Converting %s\n", filename);

	// Read the file in

	if (!read_file(filename, &sound_file_info))
		return;

	// Determine the file type

	file_type = AIL_file_type(sound_file_info.data, sound_file_info.length);

	// Get the sound into normal wave format

	if (file_type == AILFILETYPE_PCM_WAV)
	{
		wave_data   = sound_file_info.data;
		wave_length = sound_file_info.length;
	}
	else if (file_type == AILFILETYPE_ADPCM_WAV)
	{
		AIL_WAV_info(sound_file_info.data, &adpcm_info);
		AIL_decompress_ADPCM(&adpcm_info, (void **)&wave_data, &wave_length);
	}
	else if (strstr(filename, ".mp3")) //if (file_type == AILFILETYPE_MPEG_L3_AUDIO)
	{
		if (!AIL_decompress_ASI(sound_file_info.data, sound_file_info.length, ".mp3", (void **)&wave_data, &wave_length, asi_callback))
		{
			printf("Could not uncompress mp3");
			convert = false;
		}
	}
	else
	{
		printf("Unknown sound format\n");
		convert = false;
	}

	// Get the new waves info

	if (convert)
	{
		AIL_WAV_info(wave_data, &mix.Info);

		/* if (wave_info.channels != 1)
		{
			printf("Cannot convert stereo samples\n");
			convert = false;
		}

		if ((wave_info.bits != 8) && (wave_info.bits != 16))
		{
			printf("Cannot convert samples that are not 8 or 16 bit\n");
			convert = false;
		}*/

		outsize = AIL_size_processed_digital_audio(44100, DIG_F_MONO_16, 1, &mix);

		final_wave_data = malloc( outsize );

		if (final_wave_data == NULL)
			return;

		final_wave_length = AIL_process_digital_audio(final_wave_data, outsize, 44100, DIG_F_MONO_16, 1, &mix);

		//if (final_wave_length != outsize)
		//	return;

		//AIL_WAV_info(final_wave_data, &wave_info);
	}

	if (convert)
	{
		// Convert into lip

		//number_of_samples = wave_info.data_len / (wave_info.bits / 8);
		number_of_samples = final_wave_length / 2;

		averaged_samples = (int *)malloc((number_of_samples + 1) * sizeof(int));

		/* if (wave_info.bits == 8)
			char_ptr = (char *)wave_info.data_ptr;
		else if (wave_info.bits == 16)
			short_ptr = (short *)wave_info.data_ptr; */

		short_ptr = (short *)final_wave_data;

		//samples_to_add = wave_info.rate / LIP_SYNC_HZ;

		samples_to_add = 44100 / LIP_SYNC_HZ;

		sample_total  = 0;
		samples_added = 0;

		number_of_averaged_samples = 0;

		// Average the samples

		for(i = 0 ; i < number_of_samples ; i++)
		{
			/* if (wave_info.bits == 8)
			{
				sample = char_ptr[i];

				if (sample < 0)
					sample = -sample;
			}
			else if (wave_info.bits == 16) */
			{
				sample = short_ptr[i];

				if (sample < 0)
					sample = -sample;
			}

			sample_total += sample;
			samples_added++;

			if ((samples_added == samples_to_add) || (i == number_of_samples - 1))
			{
				averaged_samples[number_of_averaged_samples] = sample_total / samples_added;

				//if (wave_info.bits == 16)
					averaged_samples[number_of_averaged_samples] >>= 8;

				number_of_averaged_samples++;
				sample_total  = 0;
				samples_added = 0;
			}
		}

		// Add 1 more sample to make sure mouth closes at end

		averaged_samples[number_of_averaged_samples] = 0;
		number_of_averaged_samples++;

		// Find the highest value in the averaged samples

		highest_value = 0;

		for( i = 0 ; i < number_of_averaged_samples ; i++ )
		{
			if (averaged_samples[ i ] > highest_value)
				highest_value = averaged_samples[ i ];
		}

		// Convert all samples to be in 0 to 255 range

		if (highest_value > 0)
		{
			multiplier = 255.0 / (float)highest_value;

			for( i = 0 ; i < number_of_averaged_samples ; i++ )
			{
				averaged_samples[ i ] = averaged_samples[ i ] * multiplier;
			}
		}

		// Write out new file

		//sound_length = (float)number_of_samples / (float)wave_info.rate;
		sound_length = (float)number_of_samples / 44100.0;

      if ( timeonly )
         {
         if ( timeonly_fileptr )
            {
            fprintf( timeonly_fileptr, "%s \t%7.2f Seconds.\n", filename, sound_length );
            }
         }
      else
         {
		   save_lip_sync_file(filename, averaged_samples, number_of_averaged_samples, sound_length);
         }
	}

	// Free everything

	if (sound_file_info.data != NULL)
	{
		free(sound_file_info.data);
		sound_file_info.data = NULL;
	}

	if (averaged_samples != NULL)
	{
		free(averaged_samples);
		averaged_samples = NULL;
	}

	if (final_wave_data != NULL)
	{
		free(final_wave_data);
		final_wave_data = NULL;
	}

	if ((file_type == AILFILETYPE_ADPCM_WAV) || (file_type == AILFILETYPE_MPEG_L3_AUDIO))
	{
		AIL_mem_free_lock(wave_data);
	}
}

int read_file(char *filename, sound_file_info_t *sound_file_info)
{
	FILE *sound_file;


	// Open sound file

	sound_file = fopen(filename, "rb");

	if (sound_file == NULL)
	{
		printf("Could not find file %s\n", filename);
		return false;
	}

	// Get the length of the file

	fseek(sound_file, 0, SEEK_END);
	sound_file_info->length = ftell(sound_file);
	fseek(sound_file, 0, SEEK_SET);

	// Read in file

	sound_file_info->data = (byte *)malloc(sound_file_info->length);

	if (sound_file_info->data != NULL)
	{
		fread(sound_file_info->data, 1, sound_file_info->length, sound_file);
	}
	else
	{
		printf("Could not allocate enough memory!\n");
	}

	fclose(sound_file);

	return true;
}

S32 AILCALLBACK asi_callback(U32 state, U32 value)
{
	return 1;
}

void save_lip_sync_file(char *filename, int *averaged_samples, int number_of_averaged_samples, float sound_length)
{
	FILE *lipsync_file;
	char new_filename[256];
	int i;


	// Get lip file name

	strncpy(new_filename, filename, strlen(filename) - 4);
	new_filename[strlen(filename) - 4] = 0;
	strcat(new_filename, ".lip");

	// Open lip file

	lipsync_file = fopen(new_filename, "w");

	if (lipsync_file == NULL)
	{
		printf("Could not create lipsync file %s\n", new_filename);
		return;
	}

	// Save lip information

	fprintf(lipsync_file, "%f\n", sound_length);
	fprintf(lipsync_file, "%d\n", number_of_averaged_samples);

	for(i = 0 ; i < number_of_averaged_samples ; i++)
	{
		fprintf(lipsync_file, "%d\n", averaged_samples[i]);

		/* {
			int j;
			for(j = 0 ; j < averaged_samples[i] ; j++)
				fprintf(lipsync_file, "*");

			fprintf(lipsync_file, "\n");
		} */
	}

	fclose(lipsync_file);
}

/*
======================
ProcessScript
======================
*/
qboolean ProcessScript( char * filename )
{
	byte * buffer;
   int length;

   length = TryLoadFile( filename, (void **)&buffer );

   if (length <= 0)
   {
		printf("Unable to load script file %s\n", filename);
      return false;
   }

   ParseFromMemory( (char *)buffer, length );

   // 
   // start processing
   //
   while( 1 )
   {
      if (!GetToken( true ))
         break;

      /* if ( !strcmpi( token, "name" ) )
      {
         // grab the name of the pak file
         GetToken( false );
         strcpy( destfile, token );
         printf("Pak Name: %s\n", destfile);
      }
      else */
		if ( !strcmpi( token, "include" ) )
      {
         // include some files
         GetToken( false );
         Include( token, false );
      }
      else if ( !strcmpi( token, "exclude" ) )
      {
         // exclude some files
         GetToken( false );
         Exclude( token, false );
      }
      else if ( !strcmpi( token, "includerecursive" ) )
      {
         // recursively grab some files
         GetToken( false );
         Include( token, true );
      }
      else if ( !strcmpi( token, "excluderecursive" ) )
      {
         // recursively exclude some files
         GetToken( false );
         Exclude( token, true );
      }
      else
      {
         printf( "Unknown command %s\n", token );
         return false;
      }
      //
      // eat the rest of the line
      //
      while( TokenAvailable() )
         GetToken( false );
      }

   free( buffer );
   return true;
}

/*
======================
Include
======================
*/
void Include( const char * wild, qboolean recursive )
   {
   char path[ 1024 ];
   char search[ 1024 ];
   char name[ 1024 ];

   if ( recursive )
      {
      printf( "recursively including %s\n", wild );
      }
   else
      {
      printf( "            including %s\n", wild );
      }

   memset( path, 0, sizeof( path ) );
   strcpy( name, wild );
   FixArgs( name );
   ExtractFilePath( name, path );
   ExtractFileName( name, search );
   strcpy( name, path );

   if ( !path[0] )
      strcpy( path, basedir );

   ProcessWildDirectory( path, name, search, IncludeFile, recursive );
   }

/*
======================
Exclude
======================
*/
void Exclude( const char * wild, qboolean recursive )
   {
   char path[ 1024 ];
   char search[ 1024 ];
   char name[ 1024 ];

   if ( recursive )
      {
      printf( "recursively excluding %s\n", wild );
      }
   else
      {
      printf( "            excluding %s\n", wild );
      }

   memset( path, 0, sizeof( path ) );
   strcpy( name, wild );
   FixArgs( name );
   ExtractFilePath( name, path );
   ExtractFileName( name, search );
   strcpy( name, path );

   if ( !path[0] )
      strcpy( path, basedir );

   ProcessWildDirectory( path, name, search, ExcludeFile, recursive );
   }

/*
======================
FixArgs
======================
*/
char * FixArgs(char *arg)
    {
    char *p;

    p = arg;
    DeSlashify(p);
    return arg;
    }

/*
=================
IncludeFile
filename is the name of the file we want to process
name is the path of the file (built from process_directory)
=================
*/
void IncludeFile ( char * filename, char * name )
    {
    int len;

    if ( num_files < MAX_FILES_IN_PACK )
       {
       pakfiles[ num_files ].inuse = true;
       strcpy( pakfiles[ num_files ].filename, name );
       strcat( pakfiles[ num_files ].filename, filename );
       len = strlen( pakfiles[ num_files ].filename );
	    if ( len >= MAX_PAK_FILENAME_LENGTH ) 
          {
          printf ("Filename too long: %s\n      %d chars", pakfiles[ num_files ].filename , len );
          }
       num_files++;
       }
    else
       {
       printf("exceeded MAX_PAK_FILES\n");
       }
    }
/*
=================
ExcludeFile
filename is the name of the file we want to process
name is the path of the file (built from process_directory)
=================
*/
void ExcludeFile ( char * filename, char * name )
   {
   char fullname[1024];
   int i;

   strcpy( fullname, name );
   strcat( fullname, filename );

   for( i = 0; i < num_files; i++ )
      {
      if ( !pakfiles[ i ].inuse )
         continue;
      if ( !strcmpi( fullname, pakfiles[ i ].filename ) )
         {
         pakfiles[ i ].inuse = false;
         break;
         }
      }
   }

void Usage(void)
{
	printf("Usage: lipsync <options> <list, wave, or mp3 file>\n\n");
	printf("Options:     -q for quiet (does not print most messages)\n");
	printf("             -f for force (converts all sounds regardless of timestamps)\n");
	printf("             -t dump out times only, no convert\n");

}

void ParseArguments(int argc, char* argv[])
{
   int i = 1;

   while (i < argc && argv[i][0]=='-')
   {
		switch(argv[i][1])
      {
			case 'q':
				quiet = true;
            break;
         case 'f':
            force = true;
            break;
         case 't':
            timeonly = true;
            break;
			case 'h':  
			case '?':
         default:
            Usage();
            exit( 0 );
      }
      i++;
   }
	
	if (i+1 > argc)
   {
      Usage();
      exit( 0 );
   }

   strcpy(filename, argv[i]);
}


