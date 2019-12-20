package com.example.andersontomkelski.domotica;

import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.Socket;

/**
 * Created by andersonTomkelski on 11/07/17.
 */

public class Actuator{
    public static String ip;
    public int value;
    private int id;

    public Actuator(int value, int id){
        this.value = value;
        this.id = id;
    }

    public int getId(){
        return this.id;
    }

    public String toString(){
        return this.id + ";" + this.value;
    }
}
