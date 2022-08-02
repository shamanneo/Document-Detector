#include "Foo.h"

CFoo::CFoo() 
{
    const cv::String &fileName = "C:\\Projects\\SpongeBob\\SpongeBob\\test-images\\test1.png" ;
    m_origianlImg = cv::imread(fileName, cv::IMREAD_COLOR) ; 
	if(m_origianlImg.empty())
	{
		std::cerr << 0 ;	
	}
	cv::resize(m_origianlImg, m_origianlImg, cv::Size(m_origianlImg.cols / 2, m_origianlImg.rows / 2)) ; 
} 

CFoo::~CFoo()
{
	cv::destroyAllWindows() ; 
}

void CFoo::Contours(cv::Mat &img, std::vector<cv::Point_<int>> &resPoints) 
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
	cv::approxPolyDP(newContours[0], resPoints, cv::arcLength(newContours[0], true) * 0.02, true) ; 
	if(resPoints.size() != 4)
	{
		std::cerr << "The size of result vector is not 4." ; 
	}
	for(auto it : resPoints)
	{
		cv::circle(tempImg, cv::Point_<int>(it.x, it.y), 10, cv::Scalar(255, 0, 0), 3) ; 
	}
	const std::string contourText { std::format("Contours : {}, Corners : {}", newContours.size(), resPoints.size()) } ; 
	cv::putText(tempImg, contourText, cv::Point_<int>(0, coordnates), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)) ; 
	cv::drawContours(tempImg, newContours, -1, cv::Scalar(0, 255, 0), 1, cv::LINE_AA) ; 
	m_resultImg = tempImg.clone() ;
}

void CFoo::Run()
{
	std::vector<cv::Point_<int>> resPoints ; 
	cv::Mat objectImg = m_origianlImg.clone() ; 

	// Convert image to grayscale.
	cv::cvtColor(objectImg, objectImg, cv::COLOR_BGR2GRAY) ; 

	// Binaryzation.
	cv::threshold(objectImg, objectImg, 150, 255, cv::THRESH_BINARY) ; 

	// Get Contours.
	Contours(objectImg, resPoints) ; 

	// Final Showing.
	Show() ; 
}

void CFoo::Show()
{
	cv::Mat finalImg ; 
	cv::hconcat(m_origianlImg, m_resultImg, finalImg) ; 
	cv::putText(finalImg, "Input", cv::Point_<int>(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)) ; 
	cv::putText(finalImg, "Output", cv::Point_<int>(m_origianlImg.cols, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255)) ; 
	cv::imshow("Final", finalImg) ; 
	cv::waitKey() ; 
}