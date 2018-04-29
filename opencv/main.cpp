#include <cstring>
#include <iostream>
#include <vector>

#include "opencv2/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int arg_c, char** arg_v) {
	if (arg_c == 1) {
		cout << "Usage: ./Playground -c n ... -r (record) -s (stream)" << endl;
		return 0;
	}

	vector<VideoCapture> caps;
	vector<VideoWriter> writers;
	vector<string> files;
	vector<Mat> frames;

	bool stream = false;
	bool record = false;

	for (int i = 0; i < arg_c; i++) {
		if (strcmp(arg_v[i], "-r") == 0) {
			record = true;
		}
		else if (strcmp(arg_v[i], "-c") == 0 && arg_c > ++i) {
			for (int j = 1; j <= atoi(arg_v[i]); j++) {
				cout << "Trying Cam " << arg_v[i + j] << "..." << endl;
				VideoCapture cap(atoi(arg_v[i + j]));

				cap.set(CV_CAP_PROP_FRAME_WIDTH, 850);
				cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

				if (!cap.isOpened()) {
					cout << "Failed to open camera " << arg_v[i + j] << endl;
					continue;
				}

				cout << "Camera " << arg_v[i + j] << " opened successfully" << endl;

				caps.push_back(cap);
				files.push_back("save" + to_string(j - 1) + ".avi");
				writers.push_back(VideoWriter(files[j - 1], CV_FOURCC('M', 'J', 'P', 'G'), 30, Size(caps[j - 1].get(CV_CAP_PROP_FRAME_WIDTH), caps[j - 1].get(CV_CAP_PROP_FRAME_HEIGHT)), true));
				frames.push_back(Mat());
			}
		}
		else if (strcmp(arg_v[i], "-s") == 0) {
			stream = true;
		}
	}

	while (true) {
		for (int i = 0; i < caps.size(); i++) {
			caps[i] >> frames[i];

			if (stream) {
				imshow("Frame" + to_string(i), frames[i]);
			}

			if (record) {
				writers[i].write(frames[i]);
			}
		}

		if (char(waitKey(10)) == 27) {
			break;
		}
	}

	return 0;
}
