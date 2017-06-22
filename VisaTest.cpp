// VisaTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "tchar.h"
#include "visa\\visa.h"
#pragma comment(lib, "visa\\visa32.lib")



int main(int argc, char* argv[])
{
	printf("Hello World!\n");

	ViSession m_ViHandle = NULL;
    ViSession m_ViRM = NULL;

	 
	ViStatus m_ViStat;
	m_ViStat = viOpenDefaultRM (&m_ViRM);
    if(m_ViStat != VI_SUCCESS &&
            m_ViStat != VI_WARN_CONFIG_NLOADED)
    {
		m_ViRM = NULL;
		printf("viOpenDefaultRM\n");
        return m_ViStat;
    }


        // allocate Handle
	int i = 0;

	ViAttrState state = 0;
	i++;
	m_ViStat = viOpen (m_ViRM, (ViRsrc)"GPIB0::20::INSTR", VI_LOAD_CONFIG, 1000, &m_ViHandle);
	if(m_ViStat != VI_SUCCESS &&
			m_ViStat != VI_SUCCESS_DEV_NPRESENT &&
			m_ViStat != VI_WARN_CONFIG_NLOADED)
	{
		
		printf("viOpen");
		return 0;
	}
	m_ViStat = viSetAttribute (m_ViHandle, VI_ATTR_TMO_VALUE, 10000);

	ViUInt32 reLen = 0;
	char szBuf[MAX_PATH];
	char szRe[MAX_PATH];
	char szRe2[MAX_PATH];
	strcpy(szBuf, "*IDN?");
	viWrite(m_ViHandle, (ViPBuf)szBuf, strlen(szBuf), &reLen);
	

	m_ViStat = viRead(m_ViHandle, (ViPBuf)szRe, MAX_PATH, &reLen);

	szRe[reLen] = 0;

	printf("%s\n", szRe);


	strcpy(szBuf, "SOUR:GPRF:GEN:STAT?");
	viWrite(m_ViHandle, (ViPBuf)szBuf, strlen(szBuf), &reLen);
	m_ViStat = viRead(m_ViHandle, (ViPBuf)szRe2, MAX_PATH, &reLen);

	szRe2[reLen] = 0;

	strcpy(szBuf, "CELL:POWER -70.4");
	viWrite(m_ViHandle, (ViPBuf)szBuf, strlen(szBuf), &reLen);

	strcpy(szBuf, "CELL:POWER2 -70.4");
	viWrite(m_ViHandle, (ViPBuf)szBuf, strlen(szBuf), &reLen);

	m_ViStat = viClose(m_ViHandle);

	printf("%s\n", szRe2);

	if(m_ViRM)
    {
        // allocate RM
			printf("ADSASDSAwwwwD");
        m_ViStat = viClose(m_ViRM);
        if(m_ViStat != VI_SUCCESS)
        {
			printf("ADSASDSAD");
            return -1;
        }
        m_ViRM = NULL;
    }
	return 0;
}

