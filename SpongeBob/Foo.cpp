#include "Foo.h"

CFoo::CFoo() 
{
    
} 

CFoo::~CFoo()
{
	cv::destroyAllWindows() ; 
}

void CFoo::Contours(cv::Mat &img, std::vector<cv::Point_<float>> &resPoints) 
{
	const int contourElemSize = 1000 ; 
	const int coordnates = 50 ; 
	std::vector<std::vector<cv::Point_<int>>> contours ; 
	std::vector<std::vector<cv::Point_<int>>> newContours ; 

	cv::findContours(img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE) ; 
	// Copy color image to temp image.
	cv::Mat tempImg = m_origianlImg.clone() ; 
	for(int idx = 0 ; idx < contours.size() ; idx++)
	{
		if(contours[idx].size() > contourElemSize)
		{
			newContours.push_back(contours[idx]) ; 
		}
	}
	if(newContours.size() == 0) return ; 
	cv::approxPolyDP(newContours[0], resPoints, cv::arcLength(newContours[0], true) * 0.02, true) ; 
	if(resPoints.size() != 4)
	{
		std::cerr << "The size of result vector is not 4." ; 
	}
	for(auto it : resPoints)
	{
		cv::circle(tempImg, cv::Point_<float>(it.x, it.y), 10, cv::Scalar(255, 0, 0), 3) ; 
	}
	const std::string contourText { std::format("Contours : {}, Corners : {}", newContours.size(), resPoints.size()) } ; 
	cv::putText(tempImg, contourText, cv::Point_<int>(0, coordnates), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)) ; 
	// cv::drawContours(tempImg, newContours, -1, cv::Scalar(0, 255, 0), 1, cv::LINE_AA) ; 
	m_resultImg = tempImg.clone() ;
}

void CFoo::Warp(const std::vector<cv::Point_<float>> &resPoints) 
{
	std::vector<cv::Point_<float>> corners(4) ; 
	corners[0] = resPoints[1] ;  // Left-top.
	corners[1] = resPoints[0] ;  // Right-top.
	corners[2] = resPoints[2] ;  // Left-bottom.
	corners[3] = resPoints[3] ;  // Right-bottom.

	cv::Size_<float> size { m_width, m_height } ; 
	std::vector<cv::Point_<float>> warpedCorners(4) ; 
	warpedCorners[0] = cv::Point_<float>(0, 0) ; 
	warpedCorners[1] = cv::Point_<float>(m_width, 0) ; 
	warpedCorners[2] = cv::Point_<float>(0, m_height) ; 
	warpedCorners[3] = cv::Point_<float>(m_width, m_height) ; 
	cv::Mat tempImg(size, m_origianlImg.type()) ; 
	m_warpedImg = tempImg.clone() ; 
	try
	{
		cv::Mat transMatrix = cv::getPerspectiveTransform(corners, warpedCorners) ; 
		cv::warpPerspective(m_origianlImg, m_warpedImg, transMatrix, size) ; 
	}
	catch(const cv::Exception &e)
	{
		throw e ; 
	}
}

void CFoo::Process(cv::Mat &img, cv::Mat &binImage) 
{
	std::vector<cv::Point_<float>> resPoints ; 
	cv::Mat objectImg = img.clone() ; 
	m_origianlImg = img.clone() ; 
	
	// Convert color image to grayscale.
	cv::cvtColor(objectImg, objectImg, cv::COLOR_BGR2GRAY) ; 

	// Binaryzation.
	cv::threshold(objectImg, objectImg, 150, 255, cv::THRESH_BINARY) ; 
	binImage = objectImg.clone() ; 

	// Get Contours.
	Contours(objectImg, resPoints) ; 
	
	img = m_resultImg.clone() ; 
}

void CFoo::Show()
{
	cv::Mat finalImg ; 
	cv::hconcat(m_origianlImg, m_resultImg, finalImg) ; 
	cv::hconcat(finalImg, m_warpedImg, finalImg) ; 
	
	cv::putText(finalImg, "Input", cv::Point_<int>(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)) ; 
	cv::putText(finalImg, "Output", cv::Point_<int>(m_origianlImg.cols, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)) ; 
	cv::putText(finalImg, "Final", cv::Point_<int>(m_origianlImg.cols * 2, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)) ; 
	cv::imshow("Results", finalImg) ; 
	cv::waitKey() ; 
}