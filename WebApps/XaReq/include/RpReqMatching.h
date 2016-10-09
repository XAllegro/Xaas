#ifndef RPREQMATCHING_H
#define RPREQMATCHING_H

#include <XaLibModel.h>

class RpReqMatching : public XaLibModel {

    private:
        
        typedef vector<string> VectorOfString;
        typedef map<string,string> MapString;
        
        void Dispatcher(const string &CalledEvent);
        
        void List();
	void Read();
        void Create();
        void SkeduledMatching();
        void Delete();
        void Update();
        
        string ComposeXmlReqGeneralData(string RpAtts,string Language);
        string ComposeXmlReqComposition(string RpReq_ID,string Language);
        string GetDayName(string Date);
        MapString GetRpObjGGLabels(string Language,string RpObjGGId);
        MapString GetRpAttLabels(string Language);
        string GetRpAttVLabel(string Language,string RpAttID,string RpAttVval);
        MapString GetXaDomainDesc(string Domain);
        VectorOfString Explode(const string &s,char delim);
        bool StringIsNumeric(string Str);
        bool SearchExistingMatch(DbResMap DbRes,string RpReqId,string RpReId);
        bool SearchSentMail(DbResMap DbRes,string RpReqId,string RpReId);
        void SendCustomer(string ContactName,string ContactSurname,string ContactEmail,string RoId,string RoAdminId,string RoEmail,string RoBrand,string RoName,string RoPhone,string ReqId,DbResMap DbResRe);

    protected:

    public:

        RpReqMatching();
	~RpReqMatching();
};
#endif