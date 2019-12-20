package com.example.andersontomkelski.domotica;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

public class Kitchen extends AppCompatActivity {
    private Actuator lampPWM = new Actuator(0, -1);
    private SeekBar seekBar;
    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_kitchen);

        textView = (TextView) findViewById(R.id.textView4);
        seekBar = (SeekBar) findViewById(R.id.seekBar2);

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                lampPWM.value = i;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                Toast.makeText(getApplicationContext(), "Mudando iluminação", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                textView.setText(lampPWM.value + "/" + seekBar.getMax());
                String send = lampPWM.toString();
                new SendData().execute(send);

            }
        });

    }
}
