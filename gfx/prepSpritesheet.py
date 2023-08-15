from PIL import Image
import numpy as np



im = Image.open("fonts/1.png")
pixels1 = im.load()
size1 = im.size

im = Image.open("fonts/2.png")
pixels2 = im.load()
size2 = im.size

im = Image.open("fonts/3.png")
pixels3 = im.load()
size3 = im.size

im = Image.open("fonts/4.png")
pixels4 = im.load()
size4 = im.size

frame = Image.open("fonts/frame.png")


print(size1)

final = [[[0,0,0,0] for i in range(32)] for i in range((size1[0] + size2[0] + size3[0]) * 2 + size4[0])]



for i in range(size1[0]):
    for j in range(size1[1]):
        for k in range(4):
            x = pixels1[i,j][k]
            if x == 0 and pixels1[i,j][3] != 0:
                x = 100
            final[(i // 16) * 32 + (i % 16)][j][k] = x

for i in range(size2[0]):
    for j in range(size2[1]):
        for k in range(4):
            x = pixels2[i,j][k]
            if x == 0 and pixels2[i,j][3] != 0:
                x = 100
            final[(i // 16) * 32 + (i % 16) + size1[0] * 2][j][k] = x

for i in range(size3[0]):
    for j in range(size3[1]):
        for k in range(4):
            x = pixels3[i,j][k]
            if x == 0 and pixels3[i,j][3] != 0:
                x = 100
            final[(i // 16) * 32 + (i % 16) + size1[0] * 2 + size2[0] * 2][j][k] = x

for i in range(size4[0]):
    for j in range(size4[1]):
        for k in range(4):
            x = pixels4[i,j][k]
            if x == 0 and pixels4[i,j][3] != 0:
                x = 100
            final[i + size1[0] * 2 + size2[0] * 2 + size3[0] * 2][j][k] = x

x = np.asarray(final, dtype=np.uint8)
x = np.rot90(x)
x = np.flip(x, 0)
finalIm = Image.fromarray(x)
print(finalIm.size)
#finalIm.save("spritesheetB.png")


SpritesheetIm = Image.new("RGBA", ((size1[0]+size2[0]+size3[0]) * 4 + size4[0] * 2, 32), (255,255,255,0))
print(SpritesheetIm.size)

for i in range((size1[0]+size2[0]+size3[0] +(size4[0] // 2)) // 16):
    SpritesheetIm.paste(frame,(32 * i, 0, 32 * (i + 1), 32))


SpritesheetIm.alpha_composite(finalIm)
SpritesheetIm.paste(finalIm, ((size1[0]+size2[0]+size3[0]) * 2 + size4[0], 0, (size1[0]+size2[0]+size3[0]) * 4 + size4[0] * 2, 32))

SpritesheetIm.save("spritesheetA.png")
#print((size1[0]+size2[0]+size3[0]) * 2 // 16)
