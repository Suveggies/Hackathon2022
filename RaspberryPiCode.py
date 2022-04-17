from abc import ABC, abstractmethod

class ObjectDetector(ABC):
    @abstractmethod
    def detect(self, frame, threshold=0.0):
        pass

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

# allow the camera to warm up
time.sleep(0.1)

for frame in camera.capture_continuous(rawCapture, format="bgr",
                                       use_video_port=True):

    # grab the raw NumPy array representing the image, then initialize the timestamp and occupied/unoccupied text
    image = frame.array

    result = predictor.detect(image)

    for obj in result:
        logger.info('coordinates: {} {}. class: "{}". confidence: {:.2f}'.
                    format(obj[0], obj[1], obj[3], obj[2]))

        cv2.rectangle(image, obj[0], obj[1], (0, 255, 0), 2)
        cv2.putText(image, '{}: {:.2f}'.format(obj[3], obj[2]),
                    (obj[0][0], obj[0][1] - 5),
                    cv2.FONT_HERSHEY_PLAIN, 1, (0, 255, 0), 2)


    # show the frame
    cv2.imshow("Stream", image)
    key = cv2.waitKey(1) & 0xFF
