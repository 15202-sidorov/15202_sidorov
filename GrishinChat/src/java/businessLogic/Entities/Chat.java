/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businessLogic.Entities;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

/**
 *
 * @author Илья
 */
public abstract class Chat {
    public Chat( String inputName ) {
        name = inputName;
        messages = new ArrayList<Message>();
        users = new ArrayList<UUID>();
        id = UUID.randomUUID();
    }
    
    public String getName() {
        return name;
    }
    
    public List<Message> getMessages() {
        return messages;
    }
    
    public List<UUID> getUsers() {
        return users;
    }
   
    public UUID getID() {
        return id;
    }
    
    public void addUser(UUID newUserID) {
        users.add(newUserID);
    }
    
    
    public void deleteUser(UUID userID) {
        users.remove(userID);
    }
    
    public void addMessage(Message newMessage) {
        messages.add(newMessage);
    }
    
    protected List<UUID> users;
    protected List<Message> messages;
    protected String name;
    protected UUID id;
}
