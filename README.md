# SwitchPack
A complete switch toolbox

With 19 example sketches and a complete Tutorial (tutoriel en français également).

All switches are debounced and protected against EMF interferences by the lightning fast EdgeDebouncer algorithm.

9 classes:

Debounce: debouncePin()

Contact: open(), closed(), rose(), fell()

Click: clicked()

DoubleClick: clickCount(), setMaxClicks(), setLimit()

Toggle: readStatus(), getStatus(), setStatus()

TimedClick: wasLastRead(), clickTime(), timeSinceLastClick()

Repeater: repeatRequired(), setStart(), setBurst()

ModeSwitch: readMode(), getMode(), setMode(), resetAfter()

Encoder: setPins(), setModes(), stepsPerClick(), getRotation(), getCount(), setCount(), resetCount()

