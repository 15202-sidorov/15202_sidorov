/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serverInterface;

import Utils.ResourceHandler;
import businessLogic.RegistrationController;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Илья
 */
@WebServlet(name = "RegisterServlet", urlPatterns = {"/register"})
public class RegisterServlet extends HttpServlet {
    
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        returnRegisterForm(response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        String name = request.getParameter("first_name") + " " + request.getParameter("last_name");
        String email = request.getParameter("email");
        String password = request.getParameter("password");
        if ( RegistrationController.checkInput(name) ) {
            /*
                User is already registered.
            */
            returnRegisterForm(response);
        }
        else {
            /*
                Create new user and offer him to sign in 
            */
            RegistrationController.createUser(email, name, password);
            returnSignInForm(response);
        }

    }
    
    private void returnSignInForm( HttpServletResponse response ) throws IOException {
        try (PrintWriter out = response.getWriter()) {
            ServletContext context = getServletContext();
            String fullPath = context.getRealPath("signInForm.html"); 
            String pageHTML = ResourceHandler.getDocument(fullPath);
            out.print(pageHTML);
        }
    }
    
    private void returnRegisterForm( HttpServletResponse response ) throws IOException {
        try (PrintWriter out = response.getWriter()) {
            ServletContext context = getServletContext();
            String fullPath = context.getRealPath("registerForm.html"); 
            String pageHTML = ResourceHandler.getDocument(fullPath);
            out.print(pageHTML);
        }
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Returns register page on GET and tries to register a user on POST.";
    }// </editor-fold>

}
