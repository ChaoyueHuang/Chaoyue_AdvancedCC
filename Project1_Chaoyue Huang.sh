# Project1 from Chaoyue Huang

# extract clips from chosen 007 classic titles
ffmpeg -i original.mp4 -ss 0 -t 11 clip-1.mp4
ffmpeg -i original.mp4 -ss 32 -t 37 clip-2.mp4
ffmpeg -i original.mp4 -ss 62 -t 70 clip-3.mp4
ffmpeg -i original.mp4 -ss 127 -t 134 clip-4.mp4
ffmpeg -i original.mp4 -ss 156 -t 162 clip-5.mp4
ffmpeg -i original.mp4 -ss 234 -t 230 clip-6.mp4
ffmpeg -i original.mp4 -ss 278 -t 283 clip-7.mp4
ffmpeg -i original.mp4 -ss 304 -t 309 clip-8.mp4
ffmpeg -i original.mp4 -ss 348 -t 353 clip-9.mp4
ffmpeg -i original.mp4 -ss 420 -t 425 clip-10.mp4
ffmpeg -i original.mp4 -ss 452 -t 457 clip-11.mp4

# stack two videos horizontally
ffmpeg -i clip-2.mp4 -i clip-3.mp4 -filter_complex hstack=inputs=2 part-2.mp4
ffmpeg -i clip-4.mp4 -i clip-5.mp4 -filter_complex hstack=inputs=2 part-3.mp4

# stack two videos vertically
ffmpeg -i clip-6.mp4 -i clip-7.mp4 -filter_complex vstack=inputs=2 part-4.mp4
ffmpeg -i clip-8.mp4 -i clip-9.mp4 -filter_complex vstack=inputs=2 part-5.mp4

# stack four videos vertically
ffmpeg -i part-4.mp4 -i part-5.mp4 -filter_complex vstack=inputs=2 part-6.mp4

# stack four videos horizontally
ffmpeg -i clip-4.mp4 -i clip-5.mp4 -filter_complex hstack=inputs=2 part-7.mp4

# codes for eighth part
ffmpeg -i clip-6.mp4 -i clip-6.mp4 -filter_complex vstack=inputs=2 part-8-1.mp4
ffmpeg -i part-8-1.mp4 -i part-8-1.mp4 -filter_complex hstack=inputs=2 part-8-2.mp4
ffmpeg -i part-8-2.mp4 -i part-8-2.mp4 -filter_complex hstack=inputs=2 part-8-3.mp4
ffmpeg -i part-8-3.mp4 -i part-8-3.mp4 -filter_complex vstack=inputs=2 part-8-4.mp4

# contact child clips of eight part together
ffmpeg -f concat -i join-1.txt -c copy part-8.mp4

# scale all the clips to same size
ffmpeg -i clip-1.mp4 -vf scale=1600x900 part-1.mp4
ffmpeg -i part-2.mp4 -vf scale=1600x900 part-2.mp4
ffmpeg -i part-3.mp4 -vf scale=1600x900 part-3.mp4
ffmpeg -i part-4.mp4 -vf scale=1600x900 part-4.mp4
ffmpeg -i part-5.mp4 -vf scale=1600x900 part-5.mp4
ffmpeg -i part-6.mp4 -vf scale=1600x900 part-6.mp4
ffmpeg -i part-7.mp4 -vf scale=1600x900 part-7.mp4
ffmpeg -i part-8.mp4 -vf scale=1600x900 part-8.mp4

# overlap two clips
ffmpeg \
-i part-2.mp4 -i part-3.mp4 \
-filter_complex " \
[0:v]setpts=PTS-STARTPTS, scale=480x360[top]; \
[1:v]setpts=PTS-STARTPTS, scale=480x360, \
format=yuva420p, colorchannelmixer=aa=0.5[bottom]; \
[top][bottom]overlay=shortest=1" \
-vcodec libx264 part-23.mp4

# blur a clip's background
ffmpeg -i part-4.mp4 \
-lavfi "color=color=black@.5:size=720x960:d=1[dark]; \
[0:v]crop=720:960[blurbase]; \
[blurbase]boxblur=luma_radius='min(h,w)/20':luma_power=1:chroma_radius='min(cw,ch)/20':chroma_power=1[blurred]; \
[blurred][dark]overlay[darkened]; \
[darkened]scale=1920:1080[bg]; \
[0:v]scale=-1:360[fg]; \
[bg][fg]overlay=(W-w)/2:(H-h)/2" \
part-4.mp4

# flip second part vertically
ffmpeg -i part-2.mp4 -vf vflip -c:a copy part-2.mp4

# flip sthird part horizontally
ffmpeg -i part-3.mp4 -vf hflip -c:a copy part-3.mp4

# flip fifth part horizontally
ffmpeg -i part-5.mp4 -vf hflip -c:a copy part-5.mp4

# add a black background to all the clips
ffmpeg -loop 1 -i bg.png -i part-1.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-1.mp4
ffmpeg -loop 1 -i bg.png -i part-2.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-2.mp4
ffmpeg -loop 1 -i bg.png -i part-3.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-3.mp4
ffmpeg -loop 1 -i bg.png -i part-23.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-23.mp4
ffmpeg -loop 1 -i bg.png -i part-4.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-4.mp4
ffmpeg -loop 1 -i bg.png -i part-5.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-5.mp4
ffmpeg -loop 1 -i bg.png -i part-6.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-6.mp4
ffmpeg -loop 1 -i bg.png -i part-7.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-7.mp4
ffmpeg -loop 1 -i bg.png -i part-8.mp4 -filter_complex "overlay=(main_w-overlay_w)/2:(main_h-overlay_h)/2:shortest=1" -codec:a copy -movflags +faststart part-8.mp4

# contact all the clips together
ffmpeg -f concat -i join-2.txt -c copy final.mp4
