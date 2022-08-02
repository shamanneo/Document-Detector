#pragma once
#include <iostream>
#include <format>

#pragma warning (disable : 5054) 
#include "opencv2/opencv.hpp" 

class CFoo
{ 
	private :
		cv::Mat m_origianlImg ; 
		cv::Mat m_resultImg ; 
	public :
		CFoo() ; 
		~CFoo() ; 
	public :
		void Contours(cv::Mat &img, std::vector<cv::Point_<int>> &resPoints) ; 
	public :
		void Run() ;
		void Show() ; 
} ;

