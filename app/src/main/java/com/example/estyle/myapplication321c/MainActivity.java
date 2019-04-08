package com.example.estyle.myapplication321c;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("okcpp-lib");
    }

    TextView mTV;
    String mStr = "default";
    User mUser = new User();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("JNI Demo");

        // Example of a call to a native method
        mTV = findViewById(R.id.sample_text);
        mTV.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    @Override
    protected void onPostCreate(@Nullable Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        mTV.setOnClickListener(this);

        mStr = callMyClassFromJava();
        mTV.setText(mStr);

        mUser.name = "张三";
        mUser.age = 18;
        mUser.gender = true;

        User[] users = createUsers(mUser);
        for (User user : users) {
            ZYLog.e("user: " + user + ", hash: " + user.hashCode());
        }
    }

    @Override
    public void onClick(View v) {
        nativeStartActivity(SecondActivity.class);
    }

    // c调用java
    public native String callMyClassFromJava();

    // 操作jobject
    public native User[] createUsers(User user);

    // 启动Activity
    public native void nativeStartActivity(Class clz);
}
