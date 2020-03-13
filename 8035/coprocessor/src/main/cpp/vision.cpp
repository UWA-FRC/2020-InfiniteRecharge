#include "vision.h"

void vision_main() {
  CJ::VisionTracking vision;

  cv::Mat image; // Original Image
  cv::Mat trackingImage; // Image after it has been filtered
  cv::Mat processingOutput; // Image after is has been processed

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("VisionTracking");
  table->GetEntry("RES_HEIGHT").SetDouble(Config::Vision::RES_HEIGHT);
  table->GetEntry("RES_WIDTH").SetDouble(Config::Vision::RES_WIDTH);

  auto offsetX = table->GetEntry("offsetX");
  auto offsetY = table->GetEntry("offsetY");

  inst.StartClientTeam(Config::TEAM);

  int port = 0;
#ifdef __DESKTOP__
  port = Config::Vision::Ports::DESKTOP;
#else
  port = Config::Vision::Ports::COPROCESSOR;
#endif

  vision.SetupVision(&image, port, 60, Config::Vision::RES_HEIGHT, Config::Vision::RES_WIDTH, 1, "Shooter Cam", true);
  vision.CustomTrack(&trackingImage, &image, 50, 70, 250, 255, 30, 255, 3, 1);

  double cx, cy;
  vision.Processing.visionHullGeneration.BoundingBox(&trackingImage, &processingOutput, &cx, &cy, 10);

#ifdef __DESKTOP__
  std::cout << "Exposure Might be dissabled on local machine" << std::endl;
#else
  system("v4l2-ctl -d /dev/video0 --set-ctrl=exposure_absolute=1");
#endif

  std::cout << "Vision Tracking Process Running" << std::endl;

  double _offsetX, _offsetY;
  while (true) {
    if (vision.Camera.cam.sink.GrabFrame(image) != 0) {

      // Display Image
      vision.Display("Output", &processingOutput);

      //Calc offset
      _offsetX = cx - (Config::Vision::RES_WIDTH / 2);
      _offsetY = cy - (Config::Vision::RES_HEIGHT / 2);

      table->PutBoolean("Vision Active", true);

      offsetX.SetDouble(_offsetX);
      offsetY.SetDouble(_offsetY);

      std::cout << "[INFO] X: " << _offsetX << " Y: " << _offsetY << " H: " << Config::Vision::RES_HEIGHT << " W: " << Config::Vision::RES_WIDTH << std::endl;
    } else {
      table->PutBoolean("Vision Active", false);
    }
  }
}
