/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serverInterface;

import businessLogic.Entities.PublicChat;
import businessLogic.PublicChatController;
import databaseInterface.DatabaseController;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;
import javax.websocket.OnClose;
import javax.websocket.OnMessage;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;
import org.json.JSONObject;

/**
 *
 * @author Илья
 */
@ServerEndpoint("/websocket")
public class mainWS {
    
    private static Set<Session> clients = Collections.synchronizedSet(new HashSet());
    private static Map<String, String> userProperties = Collections.synchronizedMap( new HashMap<String,String>());
        
    /*
        hanldes messages of type : 
        {
            username : 
            action : SEND_MESSAGE / EXIT / JOIN 
            message :
        }
    */
    
    @OnOpen
    public void onOpen(Session session) {
        System.out.println("Connection opened");
        clients.add(session);
    }
    
    @OnMessage
    public String onMessage(String message, Session session, boolean last) {
        try {
            
            JSONObject jsonData = new JSONObject(message);
            String userAction = jsonData.getString("action");
            String userName = jsonData.getString("username");
            String userMessage = jsonData.getString("message");
            if ( userAction.equals(JOIN_ACTION) ) {
                    //join chat
                    System.out.println(DatabaseController.getPublicChatIDbyName(userMessage));
                    System.out.println(DatabaseController.getUserIDbyName(userName));
                    clients.add(session);
                    userProperties.put(session.getId(), userMessage);
                    PublicChatController.conntectUserToChat(DatabaseController.getUserIDbyName(userName),
                                                        DatabaseController.getPublicChatIDbyName(userMessage));
                
            }
            else if ( userAction.equals(SEND_MESSAGE_ACTION) ) {
                PublicChatController.newMessage(DatabaseController.getUserIDbyName(userName),
                                                userMessage,
                                                DatabaseController.getPublicChatIDbyName(userProperties.get(session.getId())));
                
            }
            else if ( userAction.equals(EXIT_ACTION) ) {
                PublicChatController.removeUserFromChat(DatabaseController.getUserIDbyName(userName),
                                                        DatabaseController.getPublicChatIDbyName(userProperties.get(session.getId())));
            }
            
            /*
                Broadcast everything to all session which have the same CHATNAME PROPERTY including current session.
            */
            for ( Session s : clients ) {
               s.getBasicRemote().sendText(message);    
            }
            
        }
        catch ( Exception ex ) {
            System.out.println(message);
            ex.printStackTrace();
        }
        
        return null;
    }
    
    @OnClose
    public void onClose(Session session) {
        clients.remove(session);
        userProperties.remove(session.getId());
    }
   
    
    private static final String CHATNAME_PROPERTY = "CHATNAME";
    
    private static final String JOIN_ACTION = "JOIN";
    private static final String EXIT_ACTION = "EXIT";
    private static final String SEND_MESSAGE_ACTION = "SEND_MESSAGE";
    
}
