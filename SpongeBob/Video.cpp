#include "Video.h"

CVideo::CVideo() 
	: m_cap(0) 
{

}

CVideo::~CVideo() 
{

}

void CVideo::Run()
{
	CFoo foo ; 
	if(m_cap.isOpened() == false)
	{
		std::cerr << "Can't open the camera, please check your camera." ; 
		return ; 
	}
	cv::Mat img ; 
	cv::Mat binImg ; 
	cv::Mat resImg ; 
	while(true)
	{
		m_cap >> img ;
		// img.resize(img.rows / 2, img.cols / 2) ; 

		foo.Process(img, binImg) ;
		if(!img.empty()) 
		{
			// cv::cvtColor(binImg, binImg, cv::COLOR_GRAY2BGR) ; 
			// cv::hconcat(binImg, img, resImg) ; 
			cv::imshow("...", img) ; 
		}
		if(cv::waitKey(1) == 27)
		{
			break ; 
		}
	}
	return ;
}