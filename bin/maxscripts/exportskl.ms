function exportskl name start end =
(
local range = animationRange

-- HACK to prevent Max from crashing from a divide by zero.
if start == end then end = end + 0.1

animationRange = interval start end
exportFile name #noPrompt
animationRange = range
)

function exportsklf name start end rate=
(
local range = animationRange
local oldrate = frameRate

-- HACK to prevent Max from crashing from a divide by zero.
if start == end then end = end + 0.1

frameRate = rate
animationRange = interval start end
exportFile name #noPrompt
animationRange = range
frameRate = oldrate
)
