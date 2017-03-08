package com.fvu.web.action;

import java.text.SimpleDateFormat;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.ServletActionContext;
import org.apache.struts2.convention.annotation.InterceptorRef;
import org.apache.struts2.convention.annotation.ParentPackage;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.MapperFeature;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.opensymphony.xwork2.ActionSupport;

@ParentPackage("fvudefault")
@InterceptorRef(value = "fvuDefaultStack")
public class BaseAction extends ActionSupport {

    private static final long serialVersionUID = 4038310800015539228L;

    protected Map<String, Object> result = new HashMap<>();

    protected Logger gmLogger = LoggerFactory.getLogger("gm");

    private ObjectMapper getMapper() {
        ObjectMapper mapper = new ObjectMapper();
        mapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
        mapper.configure(DeserializationFeature.FAIL_ON_NULL_FOR_PRIMITIVES, false);
        mapper.setDateFormat(new SimpleDateFormat("yyyy-MM-dd"));

        return mapper;
    }

    private HttpServletResponse getOutJsonResponse() {
        HttpServletResponse response = this.response();
        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        response.setHeader("Cache-Control", "no-cache");
        return response;
    }

    protected void out(Object o) throws Exception {
        ObjectMapper mapper = this.getMapper();
        mapper.configure(JsonGenerator.Feature.WRITE_NUMBERS_AS_STRINGS, true);
        mapper.configure(SerializationFeature.FAIL_ON_EMPTY_BEANS, false);
        mapper.configure(MapperFeature.REQUIRE_SETTERS_FOR_GETTERS, true);
        mapper.setDateFormat(new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"));
        mapper.writeValue(this.getOutJsonResponse().getWriter(), o);
        this.getOutJsonResponse().getWriter().close();
    }

    protected void outJsonNumber(Object o) throws Exception {
        this.getMapper().writeValue(this.getOutJsonResponse().getWriter(), o);
    }

    /**
     * 获得request
     */
    protected HttpServletRequest request() {
        return ServletActionContext.getRequest();
    }

    /**
     * 获得response
     */
    protected HttpServletResponse response() {
        return ServletActionContext.getResponse();
    }
}
