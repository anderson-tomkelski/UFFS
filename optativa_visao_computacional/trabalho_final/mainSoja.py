import numpy as np
import cv2 as cv

def rescale_frame(frame, percent=25):  # make the video windows a bit smaller
  width = int(frame.shape[1] * percent/ 100)
  height = int(frame.shape[0] * percent/ 100)
  dim = (width, height)
  return cv.resize(frame, dim, interpolation=cv.INTER_AREA)


def adjust_gamma(image, gamma=0.5):
	invGamma = 1.0 / (gamma)
	table = np.array([((i / 255.0) ** invGamma) * 255
		for i in np.arange(0, 256)]).astype("uint8")

	return cv.LUT(image, table)

vid = cv.VideoCapture('desafioEsteira/sojaTeste.mp4')

kernel = np.ones((3,3),np.uint8)

ret, frame = vid.read()

bg = cv.imread('bg.jpg')

grayFrame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

frame_width = int(vid.get(3))
frame_height = int(vid.get(4))

mean1 = mean2 = mean3 = 0
qtd = 0

out = cv.VideoWriter('out/outputSojaTeste.avi', cv.VideoWriter_fourcc('M', 'J', 'P', 'G'), 30, (480, 270))
while(vid.isOpened()):
    #leitura do frame
    ret, frame = vid.read()
    
    if(not ret):
        break

    f1 = frame.copy()

    frame = adjust_gamma(frame, 0.8)

    frame = cv.absdiff(frame, bg)

    frame_resize = rescale_frame(frame)

    orig_image = frame_resize.copy()

    grayFrame = cv.cvtColor(frame_resize, cv.COLOR_BGR2GRAY)

    ret, thresh = cv.threshold(grayFrame, 80, 255, cv.THRESH_BINARY)
    
    contours, hierarchy = cv.findContours(thresh, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

    for i in contours:
        qtd += 1
        x, y, w, h = cv.boundingRect(i)
        color = f1[x + int(w / 3), y + int(h / 3)]
        if(y < 100 or y > 200): continue
        
        if(cv.arcLength(i, True) > 50 or cv.arcLength(i, True) < 30): continue
        cv.rectangle(orig_image, (int(x), int(y)), (x + int(w*1.2), y + int(h*1.2)), (255, 0, 255), 2)


    cv.imshow('Soja', orig_image)
    out.write(orig_image)

    cv.waitKey(50)

    if cv.waitKey(1) == 27:
        break

vid.release()
out.release()
cv.destroyAllWindows()
