package com.example.andersontomkelski.domotica;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void openLivingRoom(View view){
        Intent intent = new Intent(this, LivingRoom.class);
        startActivity(intent);
    }

    public void openKitchen(View view)
    {
        Intent intent = new Intent(this, Kitchen.class);
        startActivity(intent);
    }

    public void openConfig(View view){
        Intent intent = new Intent(this, Config.class);
        startActivity(intent);
    }
}
