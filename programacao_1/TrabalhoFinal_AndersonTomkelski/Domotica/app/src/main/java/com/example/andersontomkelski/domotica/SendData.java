package com.example.andersontomkelski.domotica;

import android.icu.text.DateFormat;
import android.os.AsyncTask;
import android.widget.Toast;

import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * Created by andersonTomkelski on 11/07/17.
 */

public class SendData extends AsyncTask<String, Void, Void> {
    @Override
    protected Void doInBackground(String... strings) {
        try{
            Socket client = new Socket(Actuator.ip, 12341);
            ObjectOutputStream send = new ObjectOutputStream(client.getOutputStream());
            send.writeObject(strings);
            send.close();
        }catch(Exception e){
        }
        return null;
    }
}
