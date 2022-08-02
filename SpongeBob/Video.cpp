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
	if(m_cap.isOpened() == false)
	{
		std::cerr << "Can't open the camera, please check your camera." ; 
		return ; 
	}
	cv::Mat img ; 
	while(true)
	{
		m_cap >> img ;
		cv::imshow("...", img) ; 
		if(cv::waitKey(1) == 27)
		{
			break ; 
		}
	}
	return ;
}