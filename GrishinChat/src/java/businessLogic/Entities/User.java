/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businessLogic.Entities;

import java.util.List;
import java.util.UUID;

/**
 *
 * @author Илья
 */
public class User {
    public User(String inputName, String inputEmail, String inputPassword) {
        name = inputName;
        email = inputEmail;
        password = inputPassword;
        id = UUID.randomUUID();
    }
    
    public String getName() {
        return name;
    }
    
    public String getEmail() {
        return email;
    }
    
    public String getPassword() {
        return password;
    }
    
    public UUID getID() {
        return id;
    }
    
  
    private String name;
    private String email;
    private String password;
    private UUID id;
}
