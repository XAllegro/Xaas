<?php

/**
 * Description of XaLibApi
 *
 * @author Alessandro Mariotti
 */

class XaTplStatus {

    static final function GetTplStatusForList(array $WsData,$i) {

        $Content="";
        if ($WsData['list']['item'][$i]['status']==0) {
                                            
        $Content.='<td class="StatusUnchangeable"><span>Unchangeable</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==1) {

            $Content.='<td class="StatusActive"><span>Active</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==2) {

            $Content.='<td class="StatusInactive"><span>Inactive</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==3) {

            $Content.='<td class="StatusArchived"><span>Archived</span></td>';

        } else if ($WsData['list']['item'][$i]['status']==4) {

             $Content.='<td class="StatusDeleted"><span>Deleted</span></td>';
        }
        
        return $Content;
    }
    
    
    /* CAMPAIGN STATUS
    1 : Scheduled	 
    2 : OnGoing
    3 : Expired	 
    4 : Paused
    */
    
    static final function GetTplCampaignStatusForList(array $WsData,$i) {

        $Content="";
        if ($WsData['list']['item'][$i]['campaign_status']==1) {

            $Content.='<td class="StatusScheduled no_wrap"><div>Scheduled</div></td>';

        } else if ($WsData['list']['item'][$i]['campaign_status']==2) {

            $Content.='<td class="StatusOnGoing no_wrap"><div>On Going</div></td>';

        } else if ($WsData['list']['item'][$i]['campaign_status']==3) {

            $Content.='<td class="StatusExpired no_wrap"><div>Expired</div></td>';

        } else if ($WsData['list']['item'][$i]['campaign_status']==4) {

             $Content.='<td class="StatusPaused no_wrap"><div>Paused</div></td>';
        }
        
        return $Content;
    }

}
?>