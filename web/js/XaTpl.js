function XaFormTpl (ModelName) {

    var XmlDoc=XaParseXml(ModelName);

    var RootElement=XmlDoc.documentElement.nodeName;

    var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//fieldset/field");

    var Controller=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/controller");    
    var Id=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/id");
    var Name=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/name");
    var Obj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/obj");
    var Evt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/evt");
    var Async=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/async");
    var Method=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/method");
    var Class=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/class");
    var EncType="multipart/form-data";

    function BuildAction(){

        var Action="javascript:XaCallAction('','obj="+Obj+"&amp;evt="+Evt+"','','"+Method+"',"+Async+",0,'','"+Id+"','StringText','','yes','');";
        return Action;
    };

    function BuildField (FieldId) {

        var Field="";

        var FId=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/id");

        //var FId=Fields[RootElement]['fieldset']['field'][FieldId]["id"];
        var FName=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/name");
        var FType=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/type");
        var FLabel=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/label");
        var FPlaceholder=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/placeholder");

        var FDefault=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/default");

        var FRequired=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/required");
        
        if (FRequired==="yes") {
            FRequired=" required=\"required\" ";
        } else {
            FRequired="";
        };

        var FRead=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/read");
        var FUpdate=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/update");
        var FSearch=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/search");
        var FSize=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/size");

        var FieldExtId=RootElement+"-"+FId;
        var FieldExtName=RootElement+"-"+FName;

        var LId=FieldId+"-label";
        var LName=FieldExtName+"-label";

        if (FType==="input-text") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<input id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></input>";

        } else if (FType==="input-email") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<input id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\"email\" pattern=\"[^ @]*@[^ @]*\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></input>";

        } else if (FType==="input-textarea") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<textarea id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></textarea>";

        } else if (FType==="select-single") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></select>";

            var FObj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/obj");
            var FEvt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/evt");

            Field+="<script>XaCreateOptions('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"','');</script>";

        } else if (FType==="select-single-ou-tree") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></select>";

            var FObj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/obj");
            var FEvt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/evt");

            Field+="<script>XaCreateOptionsOu('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"','');</script>";

        } else if (FType==="select-single-static") {

	    var OptionsNumber=XaXmlCountElementByXpath(XmlDoc,"//fieldset/field["+FieldId+"]/options/option");
	    var DefaultValue =XaXmlGetElementValueByXpath(XmlDoc,"//fieldset/field["+FieldId+"]/default");

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" >";
            Field+="<option value=\"\">... Select an option ...</option>";
            for(var i=0;i<OptionsNumber;i++) {
		var j=i+1;
		var OptValue=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/option["+j+"]/value");
		var OptText =XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/option["+j+"]/label");
		Field+="<option value=\""+OptValue+"\">"+OptText+"</option>";
            }
            Field+="</select>";

            Field+="<script>XaSelectOptions('"+FieldExtId+"','"+DefaultValue+"');</script>";

        } else {
            
        }

    return Field;
    };

    /*can access _privateProperty and call _privateMethod*/
    this.GetForm = function () {

        var Content="<form class=\"form "+Class+"\" id=\""+Id+"\""+ " name=\""+Name+"\" enctype=\""+EncType+ "\" method=\""+Method+"\""+ " action=\""+BuildAction()+ "\">";

        Content+="<fieldset>";
        Content+="<legend>"+ XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/legend")+"</legend>";
        Content+="<ul>";


        for(var i=0;i<FieldsNumber;i++) {
            var j=i+1;
            Content+="<li>"+BuildField(j)+"</li>";
        };

        Content+="</ul>";
        Content+="</fieldset>";
        Content+="<fieldset><button type=\"reset\">Reset</button><button type=\"submit\">Save</button></fieldset>";
        Content+="</form>";

        /*console.log(Content);*/
        //console.log(Fields);
        return Content;
    };
};

/* This template does not use model Xml  */
/* Column names are taken from tag names */
/* No check on permissions on fields     */
/*LIST*/
function XaListRawTpl (DataName) {

    var XmlDoc=XaParseXml(DataName);

    var RootElement=XmlDoc.documentElement.nodeName;
    var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//list/item");

    var TagsNames=Array();

    var ElementsNumbers;

    if (FieldsNumber>0) {

        ElementsNumbers=XaXmlCountElementByXpath(XmlDoc,"//list/item[0]");
    }

    function BuildHeader() {

        var ListHeader="<tr class=\"header\">";
        TagsNames=XaXmlGetTagNameByXpath(XmlDoc,"//item[1]");

        for(key in TagsNames) {
            ListHeader+="<th>"+TagsNames[key]+"</th>";
        }

        ListHeader+="</tr>";
        return ListHeader;
    };

    function BuildRow (FieldIdx) {

        var ListRow="<tr class=\"row\">";
        
        for(key in TagsNames) {

            var TagValue=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+FieldIdx+"]/"+TagsNames[key]);
            ListRow+="<td>"+TagValue+"</td>"; 
        }

    return ListRow;
    };

    this.GetList = function () {

        var Content="<table class=\"list\">";
        var Title="Titolo Lista";
 
        Content+="<tr class=\"title\"><td colspan=\"100%\"><span>"+Title+"</span><ul class=\"RightToolbar\"><li class=\"FunctionIcon Refresh\"></li><li class=\"FunctionIcon Expand\"></li></ul></td></tr>";

        Content+=BuildHeader();

        for(var i=0;i<FieldsNumber;i++) {

            Content+=BuildRow(i+1);
        };
        Content+="</table>";

        return Content;
    };
};

/*
 * @function XaCreateOptions
 * Function to Read Options From the Back End and Add them into a Select 
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 *
 * @returns {booblean} 
 * 
 */
function XaCreateOptions(controller,url,SelectId,DefaultValue){
            
    XaCallAsync(controller,url,"xml", function(XmlDoc){

        var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");

        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=1;i<FieldsNumber+1;i++) {

            var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
            var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");

            Select.options[Select.options.length] = new Option(name,id);
            if (DefaultValue===id) {
		// now the length has been updated, thus last option is length-1
                Select.options[Select.options.length -1].selected=1;
            }
        }
    });
};

/*
 * @function XaCreateOptionsWithOnChangeFunction
 * Function to Read Options From the Back End and Add them into a Select and with a CallBack function called Onchange 
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 * @param {string} function name - the callback function called Onchange
 * @returns {booblean} 
 *
 */
function XaCreateOptionsWithOnChangeFunction(controller,url,SelectId,OnChangeFunction){

    XaCallAsync(controller,url,"xml", function(XmlDoc){

        var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");

        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=1;i<FieldsNumber+1;i++) {
            
            var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
            var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");

            Select.options[Select.options.length] = new Option(name,id);
        }

        //ADDING CB FUNCTION
        Select.setAttribute("onchange", OnChangeFunction);
    });
};

/*
 * @function XaCreateOptions specialized for OU
 * Function to Read Options OU From the Back End and Add them into a Select with indentation
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 *
 * @returns {booblean} 
 * 
 */
function XaCreateOptionsOu(controller,url,SelectId,DefaultValue){

    XaCallAsync(controller,url,"xml", function(XmlDoc){

        var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");
        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=1;i<FieldsNumber+1;i++) {

            var indent="";

            var tree_level=parseInt(XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/tree_level"))+1;
            var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
            var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");

            for (var j=1;j<tree_level;j++) {
                indent=indent+"--";

                if (j===tree_level-1) {

                    indent=indent+">";
                }
            }

            Select.options[Select.options.length] = new Option(indent+name,id);
            if (DefaultValue===id) {
		// now the length has been updated, thus last option is length-1
                Select.options[Select.options.length -1].selected=1;
            }

        }
    });
};

/*
 * @function XaTreeReadBranch specialized for OU
 * Function to Read a Branch of OU
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 *
 * @returns {booblean} 
 * 
 */
function XaTreeBranchRead(controller,url,TargetId) {

    if (TargetId!=="" && XaStyleCheckClass("a-"+TargetId,"open")) {
            XaTreeBranchClose(TargetId);
 
    } else {
        
        if (TargetId!=="") {

            XaStyleSetCssClassById("a-"+TargetId,"open");

        };
    
        XaCallAsync(controller,url,"xml", function(XmlDoc){

            var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");

            var Elements="<ul>";

            for (var i=1;i<FieldsNumber+1;i++) {

                var tree_level=parseInt(XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/tree_level"))+1;
                var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
                var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");
                var BranchCallUrl="obj=XaOuUi&evt=Tree&tree_parent_ID="+id+"&tree_level="+tree_level;
                var BranchCall='XaTreeBranchRead("","'+BranchCallUrl+'","'+id+'");';

                var OuReadCallUrl="obj=XaOuUi&evt=Read&id="+id;
                OuReadCallUrl+="&lay=include";
                var UserListCallUrl="obj=XaUserUi&evt=List&tree_parent_ID="+id;
		UserListCallUrl+="&lay=include";

                var Element='<li id="'+id+'">'+

                    /*OPEN BRANCH*/
                    '<a id="a-'+id+ '" class="close" href=\'javascript:'+BranchCall+';\'></a>'+

                    /*LIST ELEMENT BRANCH*/
                    '<a class="name" href="javascript:XaCallAction(\'\',\''+UserListCallUrl+'\',\'Detail\',\'\',\'\',\'yes\',\'Detail\',\'\',\'StringHtml\',\'yes\',\'\',\'\');">'+name+'</a>'+
                    /*READ THE OU WITH EDIT*/
                    '<a class="edit" href="javascript:XaCallAction(\'\',\''+OuReadCallUrl+'\',\'Detail\',\'\',\'\',\'yes\',\'Detail\',\'\',\'StringHtml\',\'yes\',\'\',\'\');"></a>'+

                    '</li>';

                Elements+=Element;

            }

            Elements+="</ul>";

            /*FIRST LEVEL*/
            if (TargetId==="") {
                TargetId="Tree";
            }

            var OldHtml = document.getElementById(TargetId).innerHTML;
            document.getElementById(TargetId).innerHTML = OldHtml + Elements;
        });
    
    }
};

function XaTreeBranchClose(Id) {

    XaStyleSetCssClassById("a-"+Id,"close");
    XaElRemoveChildByParentId (Id,"ul");
};

/*READ*/
function XaReadTpl (ModelName,DataName) {

    var XmlDoc=XaParseXml(ModelName);
    var XmlDataDoc=XaParseXml(DataName);

    var RootElement=XmlDoc.documentElement.nodeName;

    function BuildField (FieldId) {

	var Field="";

	var FRead=XaXmlGetElementValueByXpath(XmlDoc,"//field["+FieldId+"]/read");

        if (FRead==="yes") {
            var FName =XaXmlGetElementValueByXpath(XmlDoc,"//field["+FieldId+"]/name");
            var FLabel=XaXmlGetElementValueByXpath(XmlDoc,"//field["+FieldId+"]/label");
            var FValue=XaXmlGetElementValueByXpath(XmlDataDoc,"//read/"+FName);

            Field+="<label>"+FLabel+"</label>: ";
            Field+=FValue;
        }

    return Field;
    };

    /*can access _privateProperty and call _privateMethod*/
    this.GetRead = function () {

        var Content="<div class=\"form form-1-column\">";

            var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//field");

            Content+="<ul>";
            for (var j=1; j<=FieldsNumber; j++) {
                var name =XaXmlGetElementNameByXpath(XmlDoc,"//field["+j+"]");
                Content+="<li>"+BuildField(j)+"</li>";
            };
            Content+="</ul>";

        Content+="</div>";

        return Content;
    };
};


/*
 * @function XaSelectOptions
 * Function to set options to selected state
 *
 * This function applies to both <select> and <select type="multiple"> elements
 *
 * @param {string} SelectId - The id of the select element
 * @param {string} DefaultValue - The default value for the select element
 *
 */
function XaSelectOptions(SelectId,DefaultValue) {

	var Select=document.getElementById(SelectId);

	for(var i=0;i<Select.options.length;i++) {
		if (Select.options[i].value===DefaultValue) {
			Select.options[i].selected=1;
		}
	}
};


/* UPDATE FORM */
function XaUpdateFormTpl (ModelName,DataName) {

    var XmlDoc=XaParseXml(ModelName);
    var XmlDataDoc=XaParseXml(DataName);

    var RootElement=XmlDoc.documentElement.nodeName;

    var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//fieldset/field");

    var Controller=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/controller");    
    var Id=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/id");
    var Name=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/name");
    var Obj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/obj");
    var Evt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/evt");
    var Async=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/async");
    var Method=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/method");
    var Class=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/update_form/class");
    var EncType="multipart/form-data";

    function BuildAction(){

        var Action="javascript:XaCallAction('','obj="+Obj+"&amp;evt="+Evt+"','','"+Method+"',"+Async+",0,'','"+Id+"','StringText','','yes','');";
        return Action;
    };

    function BuildField (FieldId) {

      var Field="";

      var FRead=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/read");

      /* Fields must for one thing be readable by user */

      if (FRead==="yes") {

        var FId=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/id");

        //var FId=Fields[RootElement]['fieldset']['field'][FieldId]["id"];
        var FName=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/name");
        var FType=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/type");
        var FLabel=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/label");
        var FPlaceholder=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/placeholder");
        var FDefault=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/default");
        var FRequired=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/required");
        
        if (FRequired==="yes") {
            FRequiredClause=" required=\"required\" ";
        } else {
            FRequiredClause="";
        };

        var FUpdate=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/update");

        if (FUpdate!=="yes") {
            FUpdateClause=" disabled=\"yes\" ";
        } else {
            FUpdateClause="";
        };

        var FSearch=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/search");
        var FSize=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/size");

        var FieldExtId=RootElement+"-"+FId;
        var FieldExtName=RootElement+"-"+FName;

        var LId=FieldId+"-label";
        var LName=FieldExtName+"-label";

        var Fvalue =XaXmlGetElementValueByXpath(XmlDataDoc,"//read/"+FName);

        if (FType==="input-text") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<input id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequiredClause+FUpdateClause+" autofocus=\"autofocus\" value=\""+Fvalue+"\"></input>";

        } else if (FType==="input-textarea") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<textarea id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequiredClause+FUpdateClause+" autofocus=\"autofocus\">"+Fvalue+"</textarea>";

        } else if (FType==="select-single") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequiredClause+FUpdateClause+" autofocus=\"autofocus\" ></select>";

            var FObj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/obj");
            var FEvt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/evt");
            if (FUpdate==="yes") {
              Field+="<script>XaCreateOptions('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"','"+Fvalue+"');</script>";
            } else {
              /* display only selected option */
              Field+="<script>XaCreateOptions('','obj="+FObj+"&evt="+FEvt+"&value="+FValue+"','"+FieldExtId+"','"+Fvalue+"');</script>";
            }

        } else if (FType==="select-single-ou-tree") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequiredClause+FUpdateClause+" autofocus=\"autofocus\" ></select>";

            var FObj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/obj");
            var FEvt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/evt");

            if (FUpdate==="yes") {
              Field+="<script>XaCreateOptionsOu('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"','"+Fvalue+"');</script>";
            } else {
              /* display only selected option */
              Field+="<script>XaCreateOptionsOu('','obj="+FObj+"&evt="+FEvt+"&value="+Fvalue+"','"+FieldExtId+"','"+Fvalue+"');</script>";
            }

        } else if (FType==="select-single-static") {

	    var OptionsNumber=XaXmlCountElementByXpath(XmlDoc,"//fieldset/field["+FieldId+"]/options/option");
	    var DefaultValue =XaXmlGetElementValueByXpath(XmlDoc,"//fieldset/field["+FieldId+"]/default");

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequiredClause+FUpdateClause+" autofocus=\"autofocus\" >";
            Field+="<option value=\"\">... Select an option ...</option>";
            for(var i=0;i<OptionsNumber;i++) {
		var j=i+1;
		var OptValue=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/option["+j+"]/value");
		if (FUpdate==="yes" || OptValue===Fvalue) {
			var OptText =XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/option["+j+"]/label");
			Field+="<option value=\""+OptValue+"\">"+OptText+"</option>";
		}
            }
            Field+="</select>";

            Field+="<script>XaSelectOptions('"+FieldExtId+"','"+Fvalue+"');</script>";

        } else {
            
        }

      }

    return Field;
    };

    /*can access _privateProperty and call _privateMethod*/
    this.GetForm = function () {

        var Content="<form class=\"form "+Class+"\" id=\""+Id+"\""+ " name=\""+Name+"\" enctype=\""+EncType+ "\" method=\""+Method+"\""+ " action=\""+BuildAction()+ "\">";

        var RowId =XaXmlGetElementValueByXpath(XmlDataDoc,"//read/id");
        var FieldExtName=RootElement+"-id";

        Content+="<fieldset>";
        Content+="<legend>"+ XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/update_legend")+"</legend>";

        Content+="<input type=\"hidden\" name=\""+FieldExtName+"\" value=\""+RowId+"\" />";

        Content+="<ul>";

        for(var i=0;i<FieldsNumber;i++) {
            var j=i+1;
            Content+="<li>"+BuildField(j)+"</li>";
        };

        Content+="</ul>";
        Content+="</fieldset>";
        Content+="<fieldset><button type=\"reset\">Reset</button><button type=\"submit\">Save</button></fieldset>";
        Content+="</form>";

        return Content;
    };
};

/*LIST*/
function XaListTpl (ModelName,DataName) {

    var XmlDoc=XaParseXml(ModelName);
    var XmlDataDoc=XaParseXml(DataName);

    var RootElement=XmlDoc.documentElement.nodeName;

    var DataRowNumber=XaXmlCountElementByXpath(XmlDataDoc,"//list/item");

    var FieldsToList=Array();

    function BuildTitle (FieldIdx) {

	var Title="";
	var FLabel=XaXmlGetElementValueByXpath(XmlDoc,"//field["+FieldIdx+"]/label");
	Title+=FLabel;
	return Title;
    }

    function FindFields (ItemIdx,FieldId) {

        var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//field");
 	for (var j=1; j<=FieldsNumber; j++) {
	    var FList =XaXmlGetElementValueByXpath(XmlDoc,"//field["+j+"]/list");
            if (FList==="yes") {
               FieldsToList.push(XaXmlGetElementValueByXpath(XmlDoc,"//field["+j+"]/name"));
            }
    	}
    };

    function BuildField (ItemIdx,FieldIdx) {

        var Field="";
        var FName=FieldsToList[FieldIdx-1];

        var Fvalue=XaXmlGetElementValueByXpath(XmlDataDoc,"//list/item["+ItemIdx+"]/"+FName);
        Field+=Fvalue;

        return Field;
    };

    /*can access _privateProperty and call _privateMethod*/
    this.GetList = function () {

        var Content="<div class=\"form form-1-column\">";

        if (DataRowNumber>0) {

            FindFields();

            Content+="<table>";

            Content+="<tr>";
       	    for (var j=1; j<=FieldsToList.length; j++) {
                Content+="<th>"+BuildTitle(j)+"</th>";
       	    };
            Content+="</tr>";

            for (i=1;i<=DataRowNumber;i++) {
	            Content+="<tr>";
        	    for (var j=1; j<=FieldsToList.length; j++) {
	                Content+="<td>"+BuildField(i,j)+"</td>";
        	    };
	            Content+="</tr>";
            }
            Content+="</table>";
        } else {
               Content+="<center>No data to show</center>";
        }

        Content+="</div>";

        return Content;
    };
};
