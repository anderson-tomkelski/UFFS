package com.example.andersontomkelski.domotica;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class Config extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_config);
    }

    public void setIp(View view){
        EditText editText = (EditText) findViewById(R.id.editText);
        String ip = editText.getText().toString();
        Actuator.ip = ip;
        Toast.makeText(getApplicationContext(), "IP configurado", Toast.LENGTH_SHORT).show();
    }
}