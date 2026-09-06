# Cornell Box input replay

48-second automated replay of actions a user can perform, using the unchanged
`test_maps/cornell_box.rt`, `bonus/key_events.c` and `bonus/mouse_events.c`.

All scene changes go through `key_hooks` or `mouse_hooks`. The replay never assigns
object transforms, camera parameters or the selected object directly. Keyboard
step sizes remain unchanged. This is automated callback replay, not a recording
of a person physically using the keyboard. Each output frame comes from the
actual renderer image buffer; there is no motion interpolation. The 20 fps export
rate is not a runtime performance measurement.

| Time | User action |
| --- | --- |
| 0-6s | `1`, `E`, keypad `-` 25 times: FOV 90 to 65 |
| 6-12s | Left-click Earth at (437, 225), `3`, `W`, keypad `6` four times then `4` four times |
| 12-18s | `3`, `Q`, keypad `8` twelve times then `2` twelve times: rotate only Earth |
| 18-24s | `2`, `W`, keypad `6` eight times then `4` eight times: move the one light |
| 24-30s | `1`, `Q`, keypad `4` three times, `6` six times, `4` three times: turn the camera |
| 30-36s | Click the cyan hyperboloid at (605, 225), `3`, `Q`, keypad `6` nine times to tilt 45 degrees; `E`, keypad `6` twice then `4` twice: radius 0.5 → 2.5 → 0.5 |
| 36-42s | `3`, `E`, keypad `8` three times then `2` three times: length 3 → 6 → 3 |
| 42-48s | `1`, `E`, keypad `+` 25 times then `-` 25 times: FOV 65 → 90 → 65 |

FOV means field of view (시야각). With camera position fixed, a larger FOV shows
more of the scene and makes objects appear smaller; a smaller FOV shows less of
the scene and makes objects appear larger. This changes neither object size nor
camera position. The captions show this distinction from object resizing.

The radius controls change the local X/Z scale; length controls change the local
Y scale. The hyperboloid stays selected throughout both size demonstrations.
The initial tilt also uses ordinary user key callbacks, so its length is visible.

The yellow ring marks each replayed left click. All direction keys refer to the
numeric keypad with Num Lock off. Mode and operation keys are separate presses.
No scene state is reset between chapters; return movements use inverse key inputs.

The recorder checks each key against snapshots of the camera and every object,
plane and light transform. More than one changed target aborts the recording.
Mouse picks are checked against Earth and the cyan hyperboloid. Resize checks require positive dimensions and restoration of the original radius and length; the final FOV must return to 65 degrees. `docs/record.log` contains the action trace and
the verification result. These log files are excluded from Git.

From the repository root:

```sh
make -f tools/demo/Makefile motion
# In a separate terminal, on a free display number:
/opt/X11/bin/Xvfb :97 -screen 0 1050x450x24 -nolisten tcp -ac
# Record:
DISPLAY=:97 python3 tools/demo/record.py
```

Requires X11, FFmpeg, Pillow, and AppleSDGothicNeo.ttc (edit font path for Linux).
The original source author headers and bundled third-party notices remain intact.
`mlx_linux` is fetched by the project Makefile and excluded from Git.
