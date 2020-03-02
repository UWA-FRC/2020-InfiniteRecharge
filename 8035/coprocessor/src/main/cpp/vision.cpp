#include "vision.h"

void vision_main() {
  double offsetX, offsetY;
  int ResWidth = 640, ResHeight = 480;

  double cx, cy;

  CJ::VisionTracking vision;

  cv::Mat image; // Original Image
  cv::Mat trackingImage; // Image after it has been filtered
  cv::Mat processingOutput; // Image after is has been processed

	auto inst = nt::NetworkTableInstance::GetDefault();
	auto visionTable = inst.GetTable("VisionTracking");
	auto table = visionTable->GetSubTable("Target");

	auto targetX = table->GetEntry("Target_X");
	auto targetY = table->GetEntry("Target_Y");
	// auto imageHeight = table->GetEntry("imageHeight");
	// auto imageWidth = table->GetEntry("imageWidth");

	inst.StartClientTeam(8035);

	int port = 0;

  #ifdef __DESKTOP__
  port = 1;
  #endif

	vision.SetupVision(&image, port, 60, ResHeight, ResWidth, 1, "Shooter Cam", true);
  vision.CustomTrack(&trackingImage, &image, 50, 70, 50, 255, 30, 255, 3, 1);
	vision.Processing.visionHullGeneration.BoundingBox(&trackingImage, &processingOutput, &cx, &cy, 10);

	#ifdef __DESKTOP__
	std::cout << "Exposure Might be dissabled on local machine" << std::endl;
	#else
	system("v4l2-ctl -d /dev/video0 --set-ctrl=exposure_absolute=1");
	#endif

	std::cout << "Vision Tracking Process Running" << std::endl;
	while (true) {
		if (vision.Camera.cam.sink.GrabFrame(image) != 0) {

			// Display Image
			vision.Display("Output", &processingOutput);

			//Calc offset
			offsetX = cx-(ResWidth/2);
			offsetY = cy-(ResHeight/2);

			visionTable->PutBoolean("Vision Active", true);

			targetX.SetDouble(offsetX);
			targetY.SetDouble(offsetY);
			// imageHeight.SetDouble(ResHeight);
			// imageWidth.SetDouble(ResWidth);

			std::cout << "[INFO] X: " << offsetX << " Y: " << offsetY << " H: " << ResHeight << " W: " << ResWidth << std::endl;
		} else {
			visionTable->PutBoolean("Vision Active", false);
		}
	}
}
