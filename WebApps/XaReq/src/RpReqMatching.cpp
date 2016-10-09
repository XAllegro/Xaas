#include <RpReqMatching.h>
#include <XaLibModel.h>
#include <XaLibTime.h>

RpReqMatching::RpReqMatching() {
};

void RpReqMatching::Dispatcher(const string &CalledEvent) {
	
    if (CalledEvent=="GetXmlModel"){
        this->GetXmlModel();
    }else if (CalledEvent=="List"){
        this->List();
    }else if (CalledEvent=="SkeduledMatching"){
        this->SkeduledMatching();
    }else if (CalledEvent=="Read"){
        this->Read();
    }else if (CalledEvent=="Create"){
        this->Create();
    }else if (CalledEvent=="Update"){
        this->Update();
    }else if (CalledEvent=="Delete"){
	this->Delete();
    }else {
	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
	throw 42;
    }

};

void RpReqMatching::Create(){

    // serve per registrare tutti i movimenti fatti su un matching
    // per i tipi di movimenti vedere XaDomain con domain=XaDomainMatchingMovementType
    // parametri in ingresso: RpReqMatching_ID, XaDomainMatchingMovementType_ID, note
    
    vector<string> FieldName, WhereFields;	
    vector<string> FieldValue, WhereValues;

    unique_ptr<XaLibTime> LibTime (new XaLibTime());
    string NowTimeMysql=LibTime->GetDateTimeMySql();
    
    FieldName.push_back("updated");
    FieldValue.push_back(NowTimeMysql);

    WhereFields={"id"};
    WhereValues={HTTP.GetHttpParam("RpReqMatching_ID")};

    unique_ptr<XaLibSql> LibSql (new XaLibSql());
    LibSql->Update(DB_WRITE,"RpReqMatching",FieldName,FieldValue,WhereFields,WhereValues);

    FieldName.clear();
    FieldValue.clear();
    WhereFields.clear();
    WhereValues.clear();

    CreatePrepare({"RpReqMatching"},"/RpReqMatching/fieldset/field",FieldName,FieldValue);
    RESPONSE.Content=CreateResponse(CreateExecute("RpReqMatchingHistory",FieldName,FieldValue));
    
};

void RpReqMatching::Update() {

    // parametri da passare RpReqMatching_ID, status, is_read
    string Id=HTTP.GetHttpParam("RpReqMatching_ID");
    string Status=HTTP.GetHttpParam("status");
    
    vector<string> FieldName;	
    vector<string> FieldValue;

    if (Status=="2") {
        
        FieldName={"RpReqMatching_ID","XaDomainMatchingMovementType_ID"};
        FieldValue={Id,"2805"};
        CreateExecute("RpReqMatchingHistory",FieldName,FieldValue);
        
        FieldName.clear();
        FieldValue.clear();
    }
    
    UpdatePrepare({"RpReqMatching"},"/RpReqMatching/fieldset/field",FieldName,FieldValue);

    int Updated=XaLibSql::Update(DB_WRITE,"RpReqMatching",{FieldName},{FieldValue},{"id"},{Id});
    
    string Res="";
    if (Updated==1) {
        Res="<update>"+Id+"</update>";
    } else {
        Res="<update>0</update>";
    } 
    
    RESPONSE.Content=Res;
};

void RpReqMatching::List(){
    
    string RpRo_ID=HTTP.GetHttpParam("RpRo_ID"); // deve essere preso dalla sessione
    string ContactOrRpReq_ID=HTTP.GetHttpParam("Contact_or_RpReq_ID"); // contatto o id richiesta
    string IsRead=HTTP.GetHttpParam("is_read"); // letto non letto
    string ContactPrequalif=HTTP.GetHttpParam("contact_prequalif"); // prequalifica contatto
    string Delegate=HTTP.GetHttpParam("delegate"); // incaricato
    string IsCertificate=HTTP.GetHttpParam("is_certificate"); // bollino qualita
    string XaDomainExclusivity_ID=HTTP.GetHttpParam("XaDomainExclusivity_ID"); // esclusiva-non esclusiva-verbale
    string WithPhoto=HTTP.GetHttpParam("with_photo"); // immobile con foto:1 - immobile senza foto:2

    string FilterRpReq_ID{};
    string FilterContact{};
    string FilterIsRead{};
    string FilterPrequalif{};
    string FilterDelegate{};
    string FilterIsCertificate{};
    string FilterExclusive{};
    string FilterWithPhoto{};
    
    if (ContactOrRpReq_ID!="NoHttpParam" && ContactOrRpReq_ID!="") {
        bool CheckStr=StringIsNumeric(ContactOrRpReq_ID);
        if (CheckStr==true) {
            FilterRpReq_ID=" AND RpReqMatching.RpReq_ID="+ContactOrRpReq_ID;
        } else {
            FilterContact=" AND (contact.name LIKE '%"+ContactOrRpReq_ID+"%' OR contact.surname LIKE '%"+ContactOrRpReq_ID+"%')";
        }
    }
    
    if (IsRead!="NoHttpParam" && IsRead!="") {
        FilterIsRead=" AND RpReqMatching.is_read="+IsRead;
    }
            
    if (ContactPrequalif!="NoHttpParam" && ContactPrequalif!="") {
        FilterPrequalif=" AND contact.prequalification="+ContactPrequalif;
    }
    
    if (Delegate!="NoHttpParam" && Delegate!="") {
        FilterDelegate=" AND req_req.delegate="+Delegate;
    }       
    
    if (IsCertificate!="NoHttpParam" && IsCertificate!="") {
        FilterIsCertificate=" AND RpReqMatching.is_certificate="+IsCertificate;
    }
    
    if (XaDomainExclusivity_ID!="NoHttpParam" && XaDomainExclusivity_ID!="") {
        FilterExclusive=" AND RpReqMatching.XaDomainExclusivity_ID="+XaDomainExclusivity_ID;
    }
    
    if (WithPhoto!="NoHttpParam" && WithPhoto!="") {
        FilterWithPhoto=" AND RpReqMatching.with_photo="+WithPhoto;
    }
            
    //string Qry="SELECT M.id,M.XaField_ID,M.preferred,M.position,CONCAT('data:',D.type,';base64,',D.thumbnail) thumbnail,D.type "
              // "FROM RpReqMatching M LEFT JOIN RpReqMatchingHistory D ON D.RpReqMatching_ID=M.id WHERE M.status=1  AND M.XaField_ID="+XaField_ID+" AND M.XaTable='"+XaTable+"' AND M.XaDomainMediaCategory_ID="+XaDomainMediaCategory_ID;

    string Qry="SELECT DISTINCT RpReqMatching.RpReq_ID,req_req.levels,req_req.rp_atts,req_req.geo_town_name,req_req.rp_obj,req_req.price,req_req.sqmt,req_req.delegate,req_req.matching_notice,"
            "contact.prequalification AS client_prequalif,contact.name AS client_name,contact.surname AS client_surname,contact.email AS client_email "
            "FROM req_req,contact,RpReqMatching "
            "WHERE RpReqMatching.RpReq_ID=req_req.id AND contact.id=req_req.contact_id AND RpReqMatching.status=1 "
            "AND RpReqMatching.RpRo_ID="+RpRo_ID+FilterRpReq_ID+FilterContact+FilterIsRead+FilterPrequalif+FilterDelegate+FilterIsCertificate+FilterExclusive+FilterWithPhoto+" ORDER BY RpReqMatching.RpReq_ID;";

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);
    
    string QryRe="SELECT * FROM RpReqMatching WHERE status=1 AND RpRo_ID="+RpRo_ID+FilterIsRead+FilterIsCertificate+FilterExclusive+FilterWithPhoto+" ORDER BY created DESC;";
    
    DbResMap DbResRe=XaLibSql::FreeQuerySelect(DB_READ,QryRe);

    vector<string> ListFields={"RpReq_ID","levels","geo_town_name","rp_obj","price","sqmt","delegate","matching_notice","client_prequalif","client_name","client_surname","client_email"};

    string XaDomainTaskType{};
    
    MapString LabelsSubtype = GetRpObjGGLabels("it","2"); //gg=2 richieste
    MapString MapSubType = GetXaDomainDesc("RpReSubtype");
    
    string Res="<list_req>";

	for (unsigned int j=0;j<DbRes.size();j++) {
            string ReqId=DbRes[j]["RpReq_ID"];
            string RpAtts=DbRes[j]["rp_atts"];
            
            Res.append("<item>");

            for (auto &i: ListFields) {

                    Res.append("<"+i+">");

                    if (DbRes[j][i]=="") {
                            Res.append("null");

                    } else {
                            
                        if (i=="rp_obj") {
                            Res.append(LabelsSubtype[FromIntToString(FromStringToInt(DbRes[j][i])+999)]);
                        } else {
                            Res.append(DbRes[j][i]);
                        }
                        
                    }

                    //Res.append(DbRes[j][i]);
                    Res.append("</"+i+">");

            };

            Res.append(ComposeXmlReqGeneralData(RpAtts,"it"));
            Res.append(ComposeXmlReqComposition(ReqId,"it"));
            
            Res.append("<list_match>");

                for (unsigned int k=0;k<DbResRe.size();k++) {
                    if (DbResRe[k]["RpReq_ID"]==ReqId){
                        Res.append("<item>");
                            Res.append("<id>"+DbResRe[k]["id"]+"</id>");
                            Res.append("<RpRe_ID>"+DbResRe[k]["RpRe_ID"]+"</RpRe_ID>");
                            // da sostituire con la label
                            Res.append("<XaDomainSubType>"+MapSubType[DbResRe[k]["XaDomainSubType_ID"]]+"</XaDomainSubType>");
                            if (DbResRe[k]["XaDomainTaskType_ID"]=="1011") {
                                XaDomainTaskType="vendita";
                            } else if (DbResRe[k]["XaDomainTaskType_ID"]=="1012") {
                                XaDomainTaskType="locazione";
                            }
                            Res.append("<XaDomainTaskType>"+XaDomainTaskType+"</XaDomainTaskType>");
                            Res.append("<price>"+DbResRe[k]["price"]+"</price>");
                            Res.append("<sqmt>"+DbResRe[k]["sqmt"]+"</sqmt>");
                            Res.append("<address>"+DbResRe[k]["address"]+"</address>");
                            Res.append("<geo_town_name>"+DbResRe[k]["geo_town_name"]+"</geo_town_name>");
                            Res.append("<geo_zone_name>"+DbResRe[k]["geo_zone_name"]+"</geo_zone_name>");
                            Res.append("<is_read>"+DbResRe[k]["is_read"]+"</is_read>");
                            Res.append("<created>"+DbResRe[k]["created"]+"</created>");
                            Res.append("<last_updated>"+DbResRe[k]["updated"]+"</last_updated>");
                            
                        Res.append("</item>");
                    }
                }

            Res.append("</list_match>");

            Res.append("</item>");
	};

    Res.append("</list_req>");
    
    RESPONSE.Content=Res;
    
    //RESPONSE.Content=ListResponse(DbRes,ListFields);
    
};

void RpReqMatching::Read(){

    string RpReqMatchingId=HTTP.GetHttpParam("RpReqMatching_ID");

    vector<string> WhereFields={};
    vector<string> WhereValues={};
    vector<string> OrderByFields={};
    vector<string> GroupByFields={};

    WhereFields.push_back("RpReqMatching_ID");
    WhereValues.push_back(RpReqMatchingId);

    string PassedLimit=HTTP.GetHttpParam("limit");
    int Limit={0};

    if (PassedLimit!="NoHttpParam") {
            Limit=FromStringToInt(PassedLimit);
    };

    string OrderBy=HTTP.GetHttpParam("order_by");
    string Status=HTTP.GetHttpParam("status");

    vector<string> ReturnedFields=ReadPrepare({"RpReqMatching"},"/RpReqMatching/fieldset/field");

    DbResMap DbRes=XaLibSql::Select(DB_READ,"RpReqMatchingHistory",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
    
    MapString MapMovementType = GetXaDomainDesc("XaDomainMatchingMovementType");
    
    string Res="<list>";

    for (unsigned int j=0;j<DbRes.size();j++) {

            Res.append("<item>");

            for (auto &i: ReturnedFields) {

                    Res.append("<"+i+">");

                    if (DbRes[j][i]=="") {
                        Res.append("null");

                    } else {

                        if (i=="XaDomainMatchingMovementType_ID") {
                            Res.append(MapMovementType[DbRes[j]["XaDomainMatchingMovementType_ID"]]);
                        } else {
                            Res.append(DbRes[j][i]);
                        }
                    }

                    //Res.append(DbRes[j][i]);
                    Res.append("</"+i+">");

            };

            Res.append("</item>");
    };

    Res.append("</list>");
    
    RESPONSE.Content=Res;
    
    //RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
        
};

void RpReqMatching::SkeduledMatching(){

    unique_ptr<XaLibTime> LibTime (new XaLibTime());
    
    string Now=LibTime->GetDateMySql();
    
    string DayName=GetDayName(Now);
    //string DayName="tue";
    
    if (DayName=="sun") {
        RESPONSE.Content="<matching>domenica non eseguito ok</matching>";
        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"matching ok -> domenica non eseguito");
    } else {
        LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"inizio matching del giorno -> "+DayName);
        
        string QryNew="SELECT RpReq_ID,RpRe_ID FROM RpReqMatching WHERE status IN (1,2);";
                
        DbResMap DbResNew=XaLibSql::FreeQuerySelect(DB_READ,QryNew);
               
        string Qry="SELECT m.req_req_id,m.ro_ro_id,m.us_us_id,m."+DayName+" AS list_re_id,r.matching_notice "
                   "FROM matching_history m LEFT JOIN req_req r ON r.id=m.req_req_id WHERE "+DayName+" !=0;";
                
        DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);
        
        string StrListReRe{};
        for (unsigned int i=0; i<DbRes.size();i++){
            StrListReRe.append(DbRes[i]["list_re_id"]+",");
        }
        int StrListReReSize=StrListReRe.size()-1;
        StrListReRe=StrListReRe.substr (0,StrListReReSize);
        
        //LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"lista immobili -> "+StrListReRe);

        string QryRe="SELECT id,rp_obj_g,rp_obj,price,sqmt,exclusive,task_type,is_active,geo_zone_name,is_certificate,CONCAT(address,', ',cap,' ',geo_town_name) AS address,geo_town_name "
                     "FROM re_re WHERE id IN ("+StrListReRe+")";
                
        DbResMap DbResRe=XaLibSql::FreeQuerySelect(DB_READ,QryRe);
        
        string QrySentMail="SELECT req_req_id,re_re_id FROM matching_sent_history "
                           "WHERE sent=1 AND sent_matching_date like '"+Now+"%'";
                
        DbResMap DbResSentMail=XaLibSql::FreeQuerySelect(DB_READ,QrySentMail);
        
        string QryXaDomainType="SELECT id,old_id FROM XaDomain where domain = 'RpReType';";
                
        DbResMap DbResXaDomainType=XaLibSql::FreeQuerySelect(DB_READ,QryXaDomainType);
        
        map<string,string> MapType;
        for (unsigned int i=0; i<DbResXaDomainType.size();i++){
            string rp_obj_g=DbResXaDomainType[i]["old_id"];
            
            MapType[rp_obj_g]=DbResXaDomainType[i]["id"];
        }
        
        string QryXaDomainSubType="SELECT id,old_id FROM XaDomain where domain = 'RpReSubType';";
                
        DbResMap DbResXaDomainSubType=XaLibSql::FreeQuerySelect(DB_READ,QryXaDomainSubType);
        
        map<string,string> MapSubType;
        for (unsigned int i=0; i<DbResXaDomainSubType.size();i++){
            string rp_obj=DbResXaDomainSubType[i]["old_id"];
            
            MapSubType[rp_obj]=DbResXaDomainSubType[i]["id"];
        }
        
        string QryPhoto="SELECT COUNT(id) AS tot_photo,re_re_id FROM photo"
                        " WHERE is_active=1 AND re_re_id IN ("+StrListReRe+") GROUP BY re_re_id";
                
        DbResMap DbResPhoto=XaLibSql::FreeQuerySelect(DB_READ,QryPhoto);
        
        map<string,string> MapPhoto;
        for (unsigned int i=0; i<DbResPhoto.size();i++){
            string id=DbResPhoto[i]["re_re_id"];
            
            MapPhoto[id]=DbResPhoto[i]["tot_photo"];
        }
        
        map<string, map<string,string> > MapRe;
        for (unsigned int i=0; i<DbResRe.size();i++){
            string ReId=DbResRe[i]["id"];
            string XaDomainTaskType_ID{};
            if (DbResRe[i]["task_type"]=="1") {
                XaDomainTaskType_ID="1011";
            } else if (DbResRe[i]["task_type"]=="2") {
                XaDomainTaskType_ID="1012";
            }
            string XaDomainExclusivity_ID{};
            if (DbResRe[i]["exclusive"]=="1") {
                XaDomainExclusivity_ID="1013";
            } else if (DbResRe[i]["exclusive"]=="2") {
                XaDomainExclusivity_ID="1014";
            } else if (DbResRe[i]["exclusive"]=="3") {
                XaDomainExclusivity_ID="1015";
            }
            
            string WithPhoto="1";
            if (MapPhoto[ReId]=="") {
                WithPhoto="2";
            }
            
            MapRe[ReId]["price"]=DbResRe[i]["price"];
            MapRe[ReId]["sqmt"]=DbResRe[i]["sqmt"];
            MapRe[ReId]["address"]=DbResRe[i]["address"];
            MapRe[ReId]["is_certificate"]=DbResRe[i]["is_certificate"];
            MapRe[ReId]["geo_town_name"]=DbResRe[i]["geo_town_name"];
            MapRe[ReId]["geo_zone_name"]=DbResRe[i]["geo_zone_name"];
            MapRe[ReId]["XaDomainTaskType_ID"]=XaDomainTaskType_ID;
            MapRe[ReId]["XaDomainExclusivity_ID"]=XaDomainExclusivity_ID;
            MapRe[ReId]["XaDomainType_ID"]=MapType[DbResRe[i]["rp_obj_g"]];
            MapRe[ReId]["XaDomainSubType_ID"]=MapSubType[DbResRe[i]["rp_obj"]];
            MapRe[ReId]["with_photo"]=WithPhoto;
        }
        
        // ADD in RpReqMatching e in RpReqMatchingHistory
        for (unsigned int i=0; i<DbRes.size();i++){
            VectorOfString ListReRe=Explode(DbRes[i]["list_re_id"],',');
            string MatchingNotice=DbRes[i]["matching_notice"];
            string Sent="3"; //non inviare email
            if (MatchingNotice=="1") {
                Sent="2"; //inviare email
            }
            
            for (unsigned int j=0; j<ListReRe.size();j++){
                //LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"req: "+DbRes[i]["req_req_id"]+" re: "+ListReRe[j]);
            
                bool MatchingExists=SearchExistingMatch(DbResNew,DbRes[i]["req_req_id"],ListReRe[j]);
                
                if (MatchingExists==false) {
                    LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"ADD in RpReqMatching req: "+DbRes[i]["req_req_id"]+" re: "+ListReRe[j]);
                
                    vector<string> FieldName,FieldValue;	
                    
                    FieldName={"RpReq_ID","RpRe_ID","RpRo_ID","XaUser_ID","is_sent","is_read","price","sqmt","address","is_certificate","geo_zone_name","XaDomainTaskType_ID","XaDomainExclusivity_ID","XaDomainType_ID","XaDomainSubType_ID","with_photo","geo_town_name"};
                    
                    FieldValue={DbRes[i]["req_req_id"],ListReRe[j],DbRes[i]["ro_ro_id"],DbRes[i]["us_us_id"],Sent,"2",MapRe[ListReRe[j]]["price"],MapRe[ListReRe[j]]["sqmt"],MapRe[ListReRe[j]]["address"],MapRe[ListReRe[j]]["is_certificate"],MapRe[ListReRe[j]]["geo_zone_name"],MapRe[ListReRe[j]]["XaDomainTaskType_ID"],MapRe[ListReRe[j]]["XaDomainExclusivity_ID"],MapRe[ListReRe[j]]["XaDomainType_ID"],MapRe[ListReRe[j]]["XaDomainSubType_ID"],MapRe[ListReRe[j]]["with_photo"],MapRe[ListReRe[j]]["geo_town_name"]};
                            
                    
                    int NextId = CreateExecute("RpReqMatching",FieldName,FieldValue);
                    
                    FieldName={"RpReqMatching_ID","XaDomainMatchingMovementType_ID"};
                    
                    FieldValue={FromIntToString(NextId),"2800"};
                    
                    CreateExecute("RpReqMatchingHistory",FieldName,FieldValue);
                    
                    // quando l invio mail sara fatto da c++ eliminare questa parte
                    bool SentMail=SearchSentMail(DbResSentMail,DbRes[i]["req_req_id"],ListReRe[j]);
                    
                    if (SentMail==true){
                        FieldName={"RpReqMatching_ID","XaDomainMatchingMovementType_ID"};
                    
                        FieldValue={FromIntToString(NextId),"2801"};
                    
                        CreateExecute("RpReqMatchingHistory",FieldName,FieldValue);
                    }
                
                }
                
            }
            
        }
        
        // parte di invio email da finire
        // agenzie a cui mandare le email
        /*
        string QryRo="SELECT DISTINCT ro_ro.id,ro_ro.us_us_id,ro_ro.email,ro_ro.rp_brand_id AS brand,ro_ro.name AS name,ro_ro.phone FROM ro_ro,RpReqMatching "
                     "WHERE ro_ro.rp_country_id!=2 AND ro_ro.is_active=1  AND ro_ro.rp_brand_id!=10  AND ro_ro.id=RpReqMatching.RpRo_ID AND RpReqMatching.is_sent=2 AND RpReqMatching.status=1;";
                
        DbResMap DbResRo=XaLibSql::FreeQuerySelect(DB_READ,QryRo);
        
        for (unsigned int i=0; i<DbResRo.size();i++){
            string RoId=DbResRo[i]["id"];
            string RoAdminId=DbResRo[i]["us_us_id"];
            string RoEmail=DbResRo[i]["email"];
            string RoBrand=DbResRo[i]["brand"];
            string RoName=DbResRo[i]["name"];
            string RoPhone=DbResRo[i]["phone"];
            
            string QryRe="SELECT req_req.delegate,req_req.rp_obj_g AS req_rp_obj_g,req_req.rp_obj AS req_rp_obj,RpReqMatching.RpReq_ID,RpReqMatching.XaUser_ID,RpReqMatching.RpRe_ID,"
                          "contact.name AS client_name,contact.surname AS client_surname,contact.email AS client_email,"
                          "RpReqMatching.XaDomainType_ID,RpReqMatching.XaDomainSubType_ID,RpReqMatching.XaDomainTaskType_ID,RpReqMatching.price,"
                          "RpReqMatching.sqmt,RpReqMatching.geo_town_name,RpReqMatching.geo_zone_name "
                          "FROM req_req,contact,RpReqMatching "
                          "WHERE RpReqMatching.is_sent=2 AND RpReqMatching.RpReq_ID=req_req.id AND contact.id=req_req.contact_id "
                          "AND (contact.email IS NOT NULL AND contact.email!='') AND RpReqMatching.status=1 "
                          "AND RpReqMatching.RpRo_ID="+RoId+" "
                          "ORDER BY RpReqMatching.RpReq_ID";
            
            DbResMap DbResRe=XaLibSql::FreeQuerySelect(DB_READ,QryRe);
            
            string QryReq="SELECT DISTINCT RpReqMatching.RpReq_ID,contact.name AS client_name,contact.surname AS client_surname,contact.email AS client_email FROM req_req,contact,RpReqMatching "
                          "WHERE RpReqMatching.is_sent=2 AND RpReqMatching.RpReq_ID=req_req.id AND contact.id=req_req.contact_id "
                          "AND (contact.email IS NOT NULL AND contact.email!='') AND RpReqMatching.status=1 "
                          "AND RpReqMatching.RpRo_ID="+RoId+" "
                          "ORDER BY RpReqMatching.RpReq_ID;";
            
            DbResMap DbResReq=XaLibSql::FreeQuerySelect(DB_READ,QryReq);
            
            for (unsigned int j=0; j<DbResReq.size();j++){
                string ReqId=DbResReq[j]["RpReq_ID"];
                string ContactName=DbResReq[j]["client_name"];
                string ContactSurname=DbResReq[j]["client_surname"];
                string ContactEmail=DbResReq[j]["client_email"];
                // invia email al contatto 
                SendCustomer(ContactName,ContactSurname,ContactEmail,RoId,RoAdminId,RoEmail,RoBrand,RoName,RoPhone,ReqId,DbResRe);
                // prepara parte della mail per agenzia
            }
        
            // invia la mail all agenzia
            
        } */
        
        RESPONSE.Content="<matching>"+DayName+" ok</matching><return_code>1</return_code>";
        
    }
    
    
    
    

    //FieldName.push_back("RpRe_ID");
    //FieldValue.push_back(HTTP.GetHttpParam("RpReqMatching-RpRe_ID"));

    //CreatePrepare({"RpReqMatching"},"/RpReqMatching/fieldset/field",FieldName,FieldValue);
    //CreateExecute("RpReqMatching",FieldName,FieldValue);
};

void RpReqMatching::Delete(){

    int DeletedId = DeleteExecute("RpReqMatching",HTTP.GetHttpParam("id"));
    RESPONSE.Content = DeleteResponse(DeletedId);
};

string RpReqMatching::GetDayName(string Date) {

    string DayName{};

    string Qry="SELECT WEEKDAY('"+Date+"') AS week_day;";
                
    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);
    
    string WeekDay=DbRes[0]["week_day"];
    
    if (WeekDay=="0") {
        DayName="mon";
    } else if (WeekDay=="1") {
        DayName="tue";
    } else if (WeekDay=="2") {
        DayName="wed";
    } else if (WeekDay=="3") {
        DayName="thu";
    } else if (WeekDay=="4") {
        DayName="fri";
    } else if (WeekDay=="5") {
        DayName="sat";
    } else if (WeekDay=="6") {
        DayName="sun";
    }
    
    return DayName;
};

RpReqMatching::VectorOfString RpReqMatching::Explode(const string &s,char delim) {
    
    VectorOfString result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
};

RpReqMatching::MapString RpReqMatching::GetRpObjGGLabels(string Language,string RpObjGGId){
	
    MapString Labels;

    string Qry="SELECT id,disp FROM rp_label_"+Language+" WHERE id IN (SELECT SUM(999+id) label_id FROM rp_obj WHERE rp_obj_g_id IN (SELECT id FROM rp_obj_g WHERE rp_obj_g_g_id="+RpObjGGId+") AND is_active=1 GROUP BY id)";

    unique_ptr<XaLibSql> LibSql (new XaLibSql());

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

    for (unsigned int i=0; i<DbRes.size();i++){
        Labels[DbRes[i]["id"]]=DbRes[i]["disp"];
    }

    return Labels;

};

RpReqMatching::MapString RpReqMatching::GetXaDomainDesc(string Domain){
    
    MapString MapSubType;
    
    string QryXaDomainSubType="SELECT id,description FROM XaDomain where domain = '"+Domain+"';";

    DbResMap DbResXaDomainSubType=XaLibSql::FreeQuerySelect(DB_READ,QryXaDomainSubType);

    for (unsigned int i=0; i<DbResXaDomainSubType.size();i++){
        string id=DbResXaDomainSubType[i]["id"];

        MapSubType[id]=DbResXaDomainSubType[i]["description"];
    }

    return MapSubType;
};

bool RpReqMatching::SearchExistingMatch(DbResMap DbRes,string RpReqId,string RpReId) {
    
    for (unsigned int i=0; i<DbRes.size();i++) {
        if (DbRes[i]["RpReq_ID"]==RpReqId && DbRes[i]["RpRe_ID"]==RpReId) {
            return true;
        }
    }
    return false;
};

bool RpReqMatching::SearchSentMail(DbResMap DbRes,string RpReqId,string RpReId) {
    
    for (unsigned int i=0; i<DbRes.size();i++) {
        if (DbRes[i]["req_req_id"]==RpReqId && DbRes[i]["re_re_id"]==RpReId) {
            return true;
        }
    }
    return false;
};

bool RpReqMatching::StringIsNumeric(string Str) {

    for (unsigned int i = 0; i < Str.length(); i++) {
        if (! isdigit (Str[i])) {
            return false;
        }
    }

    return true;
};

void RpReqMatching::SendCustomer(string ContactName,string ContactSurname,string ContactEmail,string RoId,string RoAdminId,string RoEmail,string RoBrand,string RoName,string RoPhone,string ReqId,DbResMap DbResRe){
    
    // fare Unclear di RoRmail RoName RoPhone
    // fare Unclear di ContactName, ContactSurname, ContactEmail
    
    string SiteUrl{};
    string DomainUrl{};
    if(RoBrand=="50"){
      SiteUrl = "http://mls.mlsopen.it/";
      DomainUrl = "http://mls.mlsopen.it";
    }else{
      SiteUrl = "https://re.replat.com/";
      DomainUrl = "https://www.replat.com";
    }
    
    string Platform="MLS Replat";
    string PlatformLink="http://www.replat.com";
    string PlatformColor="#f7941e";
    if(RoBrand=="2"){
        Platform="Frimm";
        PlatformLink="http://www.frimm.com";
        PlatformColor="#003b79";
    }else if(RoBrand=="7"){
        Platform="MLS Fiaip";
        PlatformLink="http://www.mlsfiaip.it";
        PlatformColor="#003b79";
    }else if(RoBrand=="50"){
        Platform="MLS Open";
        PlatformLink="http://www.mlsopen.it";
        PlatformColor="#003b79";
    }
    
    string MailFrom=RoEmail;
    string MailTo=ContactEmail;
    string Mailsubject=RoName+" ha degli immobili per te!"; // fare ucwords di RoName
    
    string Mailmessage="<table width='100%' cellspacing='0' cellpadding='0' style='width:100%;height:auto;margin:0;border:4px solid "+PlatformColor+";font-family:Trebuchet MS,Helvetica,serif; color:888888;'>"  
                       "<tr style='background-color:"+PlatformColor+";'><td>";
    
    if(RoBrand=="2"){
        Mailmessage+="<img src='https://re.replat.com/style/0_0/img/logo_frimm_bianco.png' border='0' style='padding:2px 10px 5px 10px;float:right'/>";
    }else if(RoBrand=="7"){
        Mailmessage+="<img src='https://re.replat.com/style/0_0/img/logo_mlsfiaip_bianco.png' border='0' style='padding:2px 10px 5px 10px;float:right'/>";
    }else if(RoBrand=="50"){
        Mailmessage+="<img src='https://re.replat.com/style/0_0/img/logo_mlsopen_bianco.png' border='0' style='padding:2px 10px 5px 10px;float:right'/>";
    }else{
        Mailmessage+="<img src='https://re.replat.com/style/0_0/img/logo_replat_bianco.png' border='0' style='padding:2px 10px 5px 10px;float:right'/>";
    }
    
    Mailmessage+="</td></tr><tr><td style='padding:10px;'>";
    
    if(RoBrand=="2"){
        Mailmessage+="<img alt='Logo agenzia' src='https://re.replat.com/style/0_0/img/affiliato_frimm.png' border='0' height='60px' style='max-height:60px'/>";
    }else if(RoBrand=="7"){
        Mailmessage+="<img alt='Logo agenzia' src='https://re.replat.com/index.php?ac=view_logo_agenzia&site="+RoAdminId+"&photo=logo' border='0' height='60px' style='max-height:60px'/>";
    }else if(RoBrand=="50"){
        Mailmessage+="<img alt='Logo agenzia' src='https://re.replat.com/index.php?ac=view_logo_agenzia&site="+RoAdminId+"&photo=logo' border='0' height='60px' style='max-height:60px'/>";
    }else{
        Mailmessage+="<img alt='Logo agenzia' src='https://re.replat.com/index.php?ac=view_logo_agenzia&site="+RoAdminId+"&photo=logo' border='0' height='60px' style='max-height:60px'/>";
    } 
    
    Mailmessage+="</td></tr>";

    Mailmessage+="<tr><td style='padding:10px;'>Gentile <span style='text-transform:capitalize'><b>"+ContactName+" "+ContactSurname+"</b></span>,\n\r\n\r<br/><br/> l'agenzia <i style='text-transform:capitalize'>"+RoName+"</i> desidera comunicarle che i seguenti immobili possono soddisfare la sua richiesta numero "+ReqId+".<br/></td></tr>";
                    
    Mailmessage+="<tr><td style='padding:10px;'>";  
    
    // 652 scheduled_matching
    
    //ciclo su DbResRe e controllare che di ogni row la richiesta sia ugule a ReqId, alrimenti non accodare al messaggio
    
};

string RpReqMatching::ComposeXmlReqGeneralData(string RpAtts,string Language){
	
    MapString LabelsAtt = GetRpAttLabels(Language); // labels degli attributi
    
    string XmlReqReqGeneralData="";
    string rp_atts{};
    //XmlReqReqGeneralData+="<general>";

    
        // rp_atts type 56,71,1;57,0,1;61,0,1;245,0,12
        unique_ptr<XaLibChar> LibChar (new XaLibChar());
        int AttsNum = LibChar->CountCharOccurrences(RpAtts,";");

        int pos = 0;
        int aaa = 0;

        string str = RpAtts;
        pos = str.find(";");

        for (int l=0; l<AttsNum+1; l++){

            string att = str.substr(aaa, pos);

            //XmlReqReqGeneralData+="<att>";
                // rp_att type 56,71,1 or 57,0,1 : str1,str2,str3
                //XmlReqReqGeneralData+="<rp_att>"+att+"</rp_att>";

                int pos1 = att.find(","); // first position ","
                string str1 = att.substr(0, pos1); // rp_att id
                att = att.substr(pos1+1);
                int pos2 = att.find(","); // second position ","
                string str2 = att.substr(0, pos2); // rp_att id child or nothing if 0
                string str2a = att.substr(pos2+1);
                int pos3 = str2a.find(","); // third position ","
                string str3 = att.substr(pos2+1, pos3); // rp_att value

                string AttName=""; string AttValue="";

                // att con label tipo select
                if (str2=="0") {
                    AttName = LabelsAtt[str1];
                    // att boolean
                    if (str1=="30"||str1=="31"||str1=="32"||str1=="33"||str1=="34"||str1=="35"||str1=="36"||str1=="38"||str1=="39"||str1=="45"||str1=="46"||str1=="47"||str1=="48"||str1=="135"||str1=="143"||str1=="144"||str1=="146"||str1=="147"||str1=="148"||str1=="149"||str1=="150"||str1=="151"||str1=="178"||str1=="183"||str1=="189"||str1=="190"||str1=="191"||str1=="192"||str1=="193"||str1=="194"||str1=="195"||str1=="196"||str1=="197"||str1=="198"||str1=="199"||str1=="206"||str1=="210"||str1=="211"||str1=="225"||str1=="226"||str1=="227"||str1=="232"||str1=="260"||str1=="261"||str1=="269"||str1=="278"||str1=="308"||str1=="309"||str1=="362"||str1=="367"||str1=="370"||str1=="372"||str1=="376") {
                        if (str3=="1") {
                            AttValue = "si";
                        } else {
                            AttValue = "no";
                        }
                    } else {
                        AttValue = GetRpAttVLabel(Language,str1,str3);
                    }
                    if (AttValue=="") {AttValue=str3;}
                } else {
                    AttName = LabelsAtt[str2];
                    AttValue = str3;
                }

                if (AttValue!="0") {
                    //XmlReqReqGeneralData+="<name>"+AttName+"</name>";
                    //XmlReqReqGeneralData+="<value>"+str3+"</value>";
                    //XmlReqReqGeneralData+="<label>"+AttValue+"</label>";
                    
                    rp_atts+=AttName+": "+AttValue+", ";
                    /*if (l<AttsNum-1){
                        rp_atts+=", ";
                    }*/
                }

            //XmlReqReqGeneralData+="</att>";

            str = str.substr(pos+1);
            pos = str.find(";");
        }


    //XmlReqReqGeneralData+="</general>";
    rp_atts=rp_atts.substr (0,rp_atts.size()-2);
    XmlReqReqGeneralData="<rp_atts>"+rp_atts+"</rp_atts>";

    return XmlReqReqGeneralData;

};

RpReqMatching::MapString RpReqMatching::GetRpAttLabels(string Language){
	
    MapString Labels;

    string Qry="SELECT rp_label_"+Language+".disp,rp_att.id FROM rp_label_it,rp_att WHERE rp_att.is_active=1 AND rp_att.id=rp_label_"+Language+".rp_att_id";

    unique_ptr<XaLibSql> LibSql (new XaLibSql());

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

    for (unsigned int i=0; i<DbRes.size();i++){
        Labels[DbRes[i]["id"]]=DbRes[i]["disp"];
    }

    return Labels;

};

string RpReqMatching::GetRpAttVLabel(string Language,string RpAttID,string RpAttVval){
	
    string Label="";

    if (RpAttVval=="") { RpAttVval="0";}

    string Qry="SELECT l.disp FROM rp_label_"+Language+" l, rp_att_v a WHERE l.rp_att_v_id=a.id AND a.rp_att_id="+RpAttID+" AND a.val='"+RpAttVval+"'";

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

    if (DbRes.size()==1) {
        Label=DbRes[0]["disp"];
    }

    return Label;

};

string RpReqMatching::ComposeXmlReqComposition(string RpReq_ID,string Language){
	
    MapString LabelsAtt = GetRpAttLabels(Language); // labels degli attributi
    string XmlReqReqComposition="";

    string Qry="SELECT level, rp_atts FROM req_req_composition WHERE req_req_id="+RpReq_ID;

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

    //XmlReqReqComposition+="<composition>";

    for (unsigned int i=0; i<DbRes.size();i++){
        XmlReqReqComposition+="<level_"+DbRes[i]["level"]+">";
            //XmlReqReqComposition+="<level_num>"+DbRes[i]["level"]+"</level_num>";
            // rp_atts type 56,71,1;57,0,1;61,0,1;245,0,12
            unique_ptr<XaLibChar> LibChar (new XaLibChar());
            int AttsNum = LibChar->CountCharOccurrences(DbRes[i]["rp_atts"],";");

            int pos = 0;
            int aaa = 0;

            string str = DbRes[i]["rp_atts"];
            pos = str.find(";");

            for (int l=0; l<AttsNum+1; l++){

                string att = str.substr(aaa, pos);

                //XmlReqReqComposition+="<att>";
                    // rp_att type 56,71,1 or 57,0,1 : str1,str2,str3
                    //XmlReqReqComposition+="<rp_att>"+att+"</rp_att>";

                    int pos1 = att.find(","); // first position ","
                    string str1 = att.substr(0, pos1); // rp_att id
                    att = att.substr(pos1+1);
                    int pos2 = att.find(","); // second position ","
                    string str2 = att.substr(0, pos2); // rp_att id child or nothing if 0
                    string str2a = att.substr(pos2+1);
                    int pos3 = str2a.find(","); // third position ","
                    string str3 = att.substr(pos2+1, pos3); // rp_att value

                    string AttName=""; string AttValue="";

                    if (str2=="0") {
                        AttName = LabelsAtt[str1];
                        AttValue = GetRpAttVLabel(Language,str1,str3);
                        if (AttValue=="") {AttValue=str3;}
                    } else {
                        AttName = AttName = LabelsAtt[str2];
                        AttValue = str3;
                    }

                    //if (AttName=="matrimoniale") {AttName="bedroom";}
                    //if (AttName=="cameretta") {AttName="small_bedroom";}
                    
                    //XmlReqReqComposition+="<name>"+AttName+"</name>";
                    //XmlReqReqComposition+="<value>"+str3+"</value>";
                    //XmlReqReqComposition+="<label>"+AttValue+"</label>";
                    XmlReqReqComposition+=AttName+": "+AttValue+", ";
                    
                //XmlReqReqComposition+="</att>";

                str = str.substr(pos+1);
                pos = str.find(";");
            }

        XmlReqReqComposition=XmlReqReqComposition.substr (0,XmlReqReqComposition.size()-2);
        XmlReqReqComposition+="</level_"+DbRes[i]["level"]+">";
    }

    //XmlReqReqComposition+="</composition>";

    return XmlReqReqComposition;

};

RpReqMatching::~RpReqMatching(){
};