# Cornell Box input replay

30-second automated replay of actions a user can perform, using the unchanged
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

The yellow ring marks the replayed left click. All direction keys refer to the
numeric keypad with Num Lock off. Mode and operation keys are separate presses.
No scene state is reset between chapters; return movements use inverse key inputs.

The recorder checks each key against snapshots of the camera and every object,
plane and light transform. More than one changed target aborts the recording.
The clicked object must be Earth. `docs/record.log` contains the action trace and
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
