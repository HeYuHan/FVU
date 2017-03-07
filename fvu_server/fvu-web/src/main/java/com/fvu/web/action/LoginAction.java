package com.fvu.web.action;

import org.apache.struts2.convention.annotation.Action;
import org.apache.struts2.convention.annotation.Namespace;
import org.apache.struts2.convention.annotation.Namespaces;
import org.apache.struts2.convention.annotation.Result;
import org.apache.struts2.convention.annotation.Results;

@Results({ @Result(name = "home", location = "/index.jsp") })
@Namespaces({ @Namespace(""), @Namespace("/") })
public class LoginAction extends BaseAction {

    private static final long serialVersionUID = 2160977346761922731L;

    @Action(value = "")
    public String go() {
        return "home";
    }

    @Action(value = "/")
    public String go1() {
        return "home";
    }

    @Action(value = "/login")
    public String index() {
        return "home";
    }

}
