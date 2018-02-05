/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businessLogic;

import businessLogic.Entities.User;
import databaseInterface.DatabaseController;
import java.util.HashMap;
import java.util.UUID;

/**
 *
 * @author Илья
 */
public class RegistrationController {
  
    
    public static User createUser(String email, String name, String password) {
        if ( !checkInput(name) ) {
            /*
                ADD USER TO THE DATABASE
            */
            User newUser = new User(name, email, password);
            DatabaseController.addUser(newUser);
            return newUser;
        }
        else {
            /*
                USER IS ALREADY ADDED TO THE DATABASE
            */
            return null;
        }
    }
    
    public static void deleteUser( UUID id ) {
        /*
            DELETE USER FROM DATABASE AND ALL CHATS
        */
        
        DatabaseController.getUsers().remove(id);
        for ( UUID chatID : DatabaseController.getPublicChats().keySet() ) {
            DatabaseController.getPublicChats().get(chatID).getUsers().remove(id);
        }
        
        for ( UUID chatID : DatabaseController.getPrivateChats().keySet() ) {
            DatabaseController.getPrivateChats().get(chatID).getUsers().remove(id);
        }
    }
    
    public static boolean checkInput( String name ) {
        if ( null == DatabaseController.getUserIDbyName(name) ) {
            return false;
        }
        
        return true;
    }
    
    public static boolean validatePassword( String name , String password ) {
        UUID uid = DatabaseController.getUserIDbyName(name);
        return DatabaseController.getUsers().get(uid).getPassword().equals(password);
    }
 
}
