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

vid = cv.VideoCapture('desafioEsteira/capsulaMarromTeste.mp4')

kernel = np.ones((3,3),np.uint8)

ret, frame = vid.read()

bg = cv.imread('bg.jpg')

grayFrame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

frame_width = int(vid.get(3))
frame_height = int(vid.get(4))

mean1 = mean2 = mean3 = 0
qtd = 0

out = cv.VideoWriter('out/outputMarromTeste.avi', cv.VideoWriter_fourcc('M', 'J', 'P', 'G'), 30, (480, 270))
while(vid.isOpened()):
    #leitura do frame
    ret, frame = vid.read()
    
    if(not ret):
        break

    f1 = frame.copy()

    frame = adjust_gamma(frame, 1.0)

    frame = cv.absdiff(frame, bg)

    frame_resize = rescale_frame(frame)

    #transformacao em cinza
    #grayFrame = cv.cvtColor(frame_resize, cv.COLOR_BGR2GRAY)

    orig_image = frame_resize.copy()

    KSIZE = 11
    ALPHA = 2
    kernel = cv.getGaussianKernel(KSIZE, 0)
    kernel = -ALPHA * kernel @ kernel.T
    kernel[KSIZE//2, KSIZE//2] += 1 + ALPHA
    filtered = cv.filter2D(frame_resize, -1, kernel)

    grayFrame = cv.cvtColor(filtered, cv.COLOR_BGR2GRAY)

    ret, thresh = cv.threshold(grayFrame, 80, 255, cv.THRESH_BINARY)
    
    contours, hierarchy = cv.findContours(thresh, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    # R 7 G 41 B 115
    for i in contours:
        qtd += 1
        x, y, w, h = cv.boundingRect(i)
        color = f1[x + int(w / 3), y + int(h / 3)]
        if(y < 100 or y > 200): continue
        #if(color[0] > 100 or color[2] < 15):
        #    cv.rectangle(orig_image, (int(x), int(y)), (x + int(w*1.2), y + int(h*1.2)), (255, 0, 255), 2)
        #    continue
        if(w * h > 1200 or w * h < 300): continue
        cv.rectangle(orig_image, (int(x), int(y)), (x + int(w*1.2), y + int(h*1.2)), (255, 0, 255), 2)

    #denoised_nlm = cv.fastNlMeansDenoisingColored(frame_resize, None, 5)

    cv.imshow('Marrom', orig_image)
    out.write(orig_image)

    cv.waitKey(50)

    if cv.waitKey(1) == 27:
        break

vid.release()
out.release()
cv.destroyAllWindows()
