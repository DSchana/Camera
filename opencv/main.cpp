#include <cstring>

#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

int main(int arg_c, char** arg_v) {
	// Video capture parameters
	VideoCapture capture(0);
	Mat frame;

	capture >> frame;

	// Video record parameters
	bool record = false;
	string file;
	VideoWriter writer;

	for (int i = 0; i < arg_c; i++) {
		if (arg_v[i] == "-r" && arg_c > i + 1) {
			record = true;
			file = arg_v[i + 1];
		}
	}

	writer = VideoWriter(file, CV_FOURCC('M', 'P', '4', '2'), 30, Size(frame.cols, frame.rows), true);

	if (!capture.isOpened()) {
		return -1;
	}

	while (capture.read(frame)) {
		imshow("Frame", frame);

		if (record) {
			writer.write(frame);
		}

		if (char(waitKey(10)) == 27) {
			break;
		}
	}

	return 0;
}
