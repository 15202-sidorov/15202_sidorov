/*

 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businessLogic.Entities;

import java.util.UUID;

/**
 *
 * @author Илья
 */
public class Message {
    public Message( String content, UUID inputUserID ) {
        userID = inputUserID;
        data = content;
    }
    
    public UUID getUserID() {
        return userID;
    }
    
    public String getMessage() {
        return data;
    }
    
    private UUID userID;
    private String data;
}
