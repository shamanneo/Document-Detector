#pragma once
#include <iostream>
#include <format>
#include "opencv.h"

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
		void Process(cv::Mat &img, cv::Mat &binImage) ; 
	public :
		void Contours(cv::Mat &img, std::vector<cv::Point_<float>> &resPoints) ; 
		void Warp(const std::vector<cv::Point_<float>> &resPoints) ; 
	public :
		void Show() ; 
} ;

