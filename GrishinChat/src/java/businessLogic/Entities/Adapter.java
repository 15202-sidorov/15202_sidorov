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
public class Adapter extends Chat {
    public Adapter( String name, SuperChat inputChat ) {
        super(name);
        scInstance = inputChat;
    }
    
    
    public String getName() {
        return scInstance.getSomethingElse().toString();
    }
       
    private SuperChat scInstance;
}
