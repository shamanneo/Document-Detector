#pragma once
#include <iostream>
#include <format>

#pragma warning (disable : 5054) 
#include "opencv2/opencv.hpp" 

class CFoo
{ 
	private  :
		float m_width ;
		float m_height ;
	private :
		cv::Mat m_origianlImg ; 
		cv::Mat m_resultImg ; 
		cv::Mat m_warpedImg ; 
	public :
		CFoo() ; 
		~CFoo() ; 
	public :
		void Contours(cv::Mat &img, std::vector<cv::Point_<float>> &resPoints) ; 
		void Warp(const std::vector<cv::Point_<float>> &resPoints) ; 
	public :
		void Run() ;
		void Show() ; 
} ;

