#include "vision.h"

void vision_main() {
  double offsetX, offsetY;
  int ResWidth = 640, ResHeight = 480;

  double cx, cy;

  CJ::VisionTracking vision;

  cv::Mat Image; // Original Image
  cv::Mat TrackingImage; // Image after it has been filtered
  cv::Mat ProcessingOutput; // Image after is has been processed

	auto inst = nt::NetworkTableInstance::GetDefault();
	auto visionTable = inst.GetTable("VisionTracking");
	auto table = visionTable->GetSubTable("Target");

	// TargetX = table->GetEntry("Target_X");
	// TargetY = table->GetEntry("Target_Y");
	// ImageHeight = table->GetEntry("ImageHeight");
	// ImageWidth = table->GetEntry("ImageWidth");

	inst.StartClientTeam(8035);

	int port = 1;
	vision.SetupVision(&Image, port, 60, ResHeight, ResWidth, 1, "Shooter Cam", true);
  vision.CustomTrack(&TrackingImage, &Image, 50, 70, 50, 255, 30, 255, 1, 1);
	vision.Processing.visionHullGeneration.BoundingBox(&TrackingImage, &ProcessingOutput, &cx, &cy, 10);
	#ifdef __DESKTOP__
	std::cout << "Exposure Might be dissabled on local machine" << std::endl;
	#else
	system("v4l2-ctl -d /dev/video0 --set-ctrl=exposure_absolute=1");
	#endif
	std::cout << "Vision Tracking Process Running" << std::endl;
	while (true) {
		if (vision.Camera.cam.sink.GrabFrame(Image) != 0) {

			// Display Image
			vision.Display("Output", &ProcessingOutput);

			//Calc offset
			offsetX = cx-(ResWidth/2);
			offsetY = cy-(ResHeight/2);

			visionTable->PutBoolean("Vision Active", true);

			// TargetX.SetDouble(offsetX);
			// TargetY.SetDouble(offsetY);
			// ImageHeight.SetDouble(ResHeight);
			// ImageWidth.SetDouble(ResWidth);

			std::cout << "[INFO] X: " << offsetX << " Y: " << offsetY << " H: " << ResHeight << " W: " << ResWidth << std::endl;
		} else {
			visionTable->PutBoolean("Vision Active", false);
		}
	}
}
