#pragma once
class CConfig
{
	
public:
	CConfig();
	~CConfig();

	void SetStyle(int n) {
		m_nStyle = n;
	}

	int GetStyle() {
		return m_nStyle;
	}

	void SetElemPath(const CString& str) {
		m_strElemPath = str;
	}

	CString GetElemPath() {
		return m_strElemPath;
	}

	static CConfig* GetSingleInstance();
	static void ReleaseInstance();

	void Save();
	//void Load();

protected:
	
	static CConfig* m_pConfig;//唯一的实例对象
	int m_nStyle;
	CString m_strElemPath;
};

