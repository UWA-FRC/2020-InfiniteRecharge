#include "vision.h"

void vision_main() {
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

  inst.StartClientTeam(Config::TEAM);

  int port = 0;
#ifdef __DESKTOP__
  port = Config::Vision::Ports::DESKTOP;
#else
  port = Config::Vision::Ports::COPROCESSOR;
#endif

  vision.SetupVision(&image, port, 60, Config::Vision::RES_HEIGHT, Config::Vision::RES_WIDTH, 1, "Shooter Cam", true);
  vision.CustomTrack(&trackingImage, &image, 50, 70, 50, 255, 30, 255, 3, 1);

  double cx, cy;
  vision.Processing.visionHullGeneration.BoundingBox(&trackingImage, &processingOutput, &cx, &cy, 10);

#ifdef __DESKTOP__
  std::cout << "Exposure Might be dissabled on local machine" << std::endl;
#else
  system("v4l2-ctl -d /dev/video0 --set-ctrl=exposure_absolute=1");
#endif

  std::cout << "Vision Tracking Process Running" << std::endl;

  double offsetX, offsetY;
  while (true) {
    if (vision.Camera.cam.sink.GrabFrame(image) != 0) {

      // Display Image
      vision.Display("Output", &processingOutput);

      //Calc offset
      offsetX = cx - (Config::Vision::RES_WIDTH / 2);
      offsetY = cy - (Config::Vision::RES_HEIGHT / 2);

      visionTable->PutBoolean("Vision Active", true);

      targetX.SetDouble(offsetX);
      targetY.SetDouble(offsetY);

      std::cout << "[INFO] X: " << offsetX << " Y: " << offsetY << " H: " << Config::Vision::RES_HEIGHT << " W: " << Config::Vision::RES_WIDTH << std::endl;
    } else {
      visionTable->PutBoolean("Vision Active", false);
    }
  }
}
