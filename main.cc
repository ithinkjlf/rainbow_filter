#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

// Color space BGR
class RainbowFilter {
public:
	RainbowFilter(double a = 0.5): alpha {a} {
			vector<vector<int> > rainbow_color_rgb(7);
			//red
			rainbow_color_rgb[0] = vector<int>{255, 0, 0};
			//orange
			rainbow_color_rgb[1] = {255, 127, 0};
			//yellow
			rainbow_color_rgb[2] = {255, 255, 0};
			//green
			rainbow_color_rgb[3] = {0, 255, 0};
			//blue
			rainbow_color_rgb[4] = {0, 0, 255};
			//indigo
			rainbow_color_rgb[5] = {75, 0, 130};
			//violet
			rainbow_color_rgb[6] = {143, 0, 255};
			
			for (int i = 0; i < 6; i++) {
				Vec3b color;
				//B
				color[0] = rainbow_color_rgb[i][2];
				//G
				color[1] = rainbow_color_rgb[i][1];
				//R
				color[2] = rainbow_color_rgb[i][0];
				colors.push_back(color);
			}
	}
	
	void filter(const Mat &img, Mat &dest) {
		int color_height = static_cast<int>(img.rows / 7);
		for (int i = 0; i < img.rows; i++) {
			int color_number = i / color_height;
			for (int j = 0; j < img.cols; j++) {
				Vec3b color;
				for (int t = 0; t < 3; t++)
					color[t] = static_cast<int>(alpha * img.at<Vec3b>(Point(j,i))[t] + (1 - alpha) * colors[color_number][t]);
				dest.at<Vec3b>(Point(j,i)) = color;
			}
		}
	}

private:
	double alpha;
	vector<Vec3b> colors; // BGR order
};


int main(int argc, char **argv) {
	
	if (argc != 3) {
		cout << "Format Error.\nUsage: ./app source_image_name destination_image_name\n";
		cout << "The extension of destination image needs to be provided." << endl;
		return 1;
	}
	
	Mat img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (img.empty()) {
		cout << "Error: image cannot be loaded." << endl;
		return 1;
	}
	
	Mat dest = img.clone();
	RainbowFilter rfilter(0.3);
	rfilter.filter(img, dest);

	imwrite(argv[2], dest);
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", dest);
	waitKey(0);
	destroyWindow("MyWindow");
	return 0;
}
