"""Cornell Box replay via existing key_hooks/mouse_hooks, exported at 20 fps.
No direct scene edits or video motion interpolation. Requires Pillow, FFmpeg, X11.
"""
from pathlib import Path
import os
import subprocess
from PIL import Image, ImageDraw, ImageFont

root=Path(__file__).resolve().parents[2]
output=root/'docs'
output.mkdir(exist_ok=True)
font=ImageFont.truetype('/System/Library/Fonts/AppleSDGothicNeo.ttc',23)
small=ImageFont.truetype('/System/Library/Fonts/AppleSDGothicNeo.ttc',17)
titles=['FOV(시야각) 좁히기','지구 선택 · 한 물체 이동','선택한 지구만 회전','광원 하나 이동','카메라 회전','물체 반경 늘리기 · 줄이기','물체 길이 늘리기 · 줄이기','FOV 넓히기 · 좁히기']
controls=['1 → E → 숫자패드 -  |  FOV 90° → 65°: 시야가 좁아지고 크게 보임','지구 클릭 → 3 → W → 숫자패드 6 / 4','3 → Q → 숫자패드 8 / 2','2 → W → 숫자패드 6 / 4','1 → Q → 숫자패드 4 / 6','3 → E → 숫자패드 6 / 4  |  반경 증가 / 감소','3 → E → 숫자패드 8 / 2  |  길이 증가 / 감소','1 → E → 숫자패드 + / -  |  FOV 65° → 90° → 65°: 위치는 그대로']
log=open(output/'record.log','w')
app=subprocess.Popen([str(root/'tools/demo/motion'),'test_maps/cornell_box.rt'],cwd=root,stdout=subprocess.PIPE,stderr=log)
temp_video=output/'demo-next.mp4'
enc=subprocess.Popen(['ffmpeg','-y','-v','error','-f','rawvideo','-pixel_format','rgb24','-video_size','1050x560','-framerate','20','-i','pipe:0','-an','-c:v','libx264','-preset','medium','-crf','19','-pix_fmt','yuv420p','-movflags','+faststart',str(temp_video)],stdin=subprocess.PIPE)
try:
 for f in range(960):
  raw=app.stdout.read(1050*450*3)
  if len(raw)!=1050*450*3: raise RuntimeError('Incomplete frame; see docs/record.log')
  frame=Image.new('RGB',(1050,560),'#101b27')
  frame.paste(Image.frombytes('RGB',(1050,450),raw),(0,62))
  draw=ImageDraw.Draw(frame)
  draw.text((24,16),'miniRT',font=font,fill='white')
  draw.text((135,20),'Cornell Box  /  '+titles[f//120],font=small,fill='#9edde2')
  draw.text((932,20),f'{f//120+1:02} / 08',font=small,fill='#bbc6d2')
  control=controls[f//120]
  if 600<=f<646: control='쌍곡면 클릭 → 3 → Q → 숫자패드 6  |  길이가 보이도록 45° 회전'
  draw.text((24,523),control,font=small,fill='#d6e1ee')
  draw.rectangle((0,557,int(1050*(f+1)/960),559),fill='#5bbbc6')
  if 120<=f<140:
   x,y=437,225+62
   draw.ellipse((x-10,y-10,x+10,y+10),outline='#ffd166',width=2)
  if 600<=f<620:
   x,y=605,225+62
   draw.ellipse((x-10,y-10,x+10,y+10),outline='#ffd166',width=2)
  if f in (90,160,298,414,514,675,765,897): frame.save(output/f'chapter-{f//120+1}.png')
  enc.stdin.write(frame.tobytes())
  if f%120==119: print('Recorded chapter',f//120+1,flush=True)
 if app.wait(timeout=5)!=0: raise RuntimeError('Input replay failed')
finally:
 enc.stdin.close()
 if app.poll() is None: app.terminate();app.wait()
 if enc.wait(timeout=30)!=0: raise RuntimeError('Encoding failed')
 log.close()
subprocess.run(['ffmpeg','-y','-v','error','-i',str(temp_video),'-vf','fps=10,scale=700:-1:flags=lanczos,split[s0][s1];[s0]palettegen=max_colors=128[p];[s1][p]paletteuse=dither=bayer:bayer_scale=3','-loop','0',str(output/'demo-next.gif')],check=True)
os.replace(temp_video,output/'demo.mp4')
os.replace(output/'demo-next.gif',output/'demo.gif')
print('Cornell Box MP4/GIF ready; input replay checks passed.',flush=True)
