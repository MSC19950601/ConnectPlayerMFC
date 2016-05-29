#include "stdafx.h"
#include "Test.h"
#include <string>
#include <cstring>
CTest::CTest()
{
}


CTest::~CTest()
{
}

void CTest::output(CGraph &graph) {
	//新建日志文件
	CStdioFile file(_T("log.txt"), CFile::modeCreate | CFile::modeReadWrite);

	CString strTmp;
	//输出顶点信息
	for (int i = 0; i < graph.GetVexnum(); i++) {
		strTmp.Format(_T("%d\t"), graph.GetVertex(i));
		file.WriteString(strTmp);
	}
	strTmp.Format(_T("\n"));
	file.WriteString(strTmp);
	strTmp.Format(_T("\n"));
	file.WriteString(strTmp);
	//输出关系矩阵
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			strTmp.Format(_T("%d\t"), graph.GetAdiMatrix(i, j));
			file.WriteString(strTmp);
		}
		strTmp.Format(_T("\n"));
		file.WriteString(strTmp);
	}
	//关闭文件
	file.Close();
}
