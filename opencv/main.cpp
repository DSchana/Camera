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
		cout << "Usage: ./Playground -c n ... -r (optional)" << endl;
		return 0;
	}

	vector<VideoCapture> caps;
	vector<VideoWriter> writers;
	vector<string> files;
	vector<Mat> frames;

	bool stream = true;
	bool record = false;

	for (int i = 0; i < arg_c; i++) {
		if (strcmp(arg_v[i], "-r") == 0) {
			record = true;
		}
		else if (strcmp(arg_v[i], "-c") == 0 && arg_c > ++i) {
			for (int j = 0; j < atoi(arg_v[i++]); j++) {
				caps.push_back(VideoCapture(atoi(arg_v[i + j])));
				files.push_back("save" + to_string(j) + ".avi");
				writers.push_back(VideoWriter(files[j], CV_FOURCC('M', 'J', 'P', 'G'), 60, Size(caps[j].get(CV_CAP_PROP_FRAME_WIDTH), caps[j].get(CV_CAP_PROP_FRAME_HEIGHT)), true));
				frames.push_back(Mat());
			}
		}
		else if (strcmp(arg_v[i], "-s") == 0) {
			stream = true;
		}
	}

	cout << caps.size() << endl;

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
