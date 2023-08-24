package com.ayaneo.security;

import androidx.appcompat.app.AppCompatActivity;

import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.ayaneo.security.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'security' library on application startup.
    static {
        System.loadLibrary("security");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
//        tv.setText(stringFromJNI());
        try {
//            PackageManager pm = context.getPackageManager();
//            PackageInfo info = pm.getPackageArchiveInfo(apkPath,
//                    PackageManager.GET_ACTIVITIES);
            PackageInfo info = getPackageManager().getPackageInfo(getPackageName(), PackageManager.GET_ACTIVITIES);
            Log.e("noah",info.applicationInfo.sourceDir);

            PackageInfo packageInfo = getPackageManager().getPackageArchiveInfo("", 0x01);
        } catch (PackageManager.NameNotFoundException e) {

        }
    }

//    /**
//     * A native method that is implemented by the 'security' native library,
//     * which is packaged with this application.
//     */
//    public native String stringFromJNI();
}