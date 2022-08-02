#pragma once
#include "opencv.h"

class CVideo
{
	private :
		cv::VideoCapture m_cap ; 
	public :
		CVideo() ; 
		~CVideo() ; 
	public :
		void Run() ; 
} ;

