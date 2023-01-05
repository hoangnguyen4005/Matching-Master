package org.cocos2dx.cpp;
import android.app.Activity;
import android.graphics.Color;
import android.view.View;
import android.widget.FrameLayout;
import androidx.annotation.NonNull;
import com.boring.matchingmaster.R;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;

public class AndroidAdManager {
    private Activity activity;
    private static AdView top_bannerView;
    private static boolean top_bannerViewShowing = false;
    private String top_bannerId;
    private String interstitialId;

    public AndroidAdManager(Activity activity) {
        this.activity = activity;
        top_bannerId = activity.getBaseContext().getString(R.string.top_bannerId);
        interstitialId = activity.getBaseContext().getString(R.string.interstitialId);
        setupAdBannerView();
    }

    public void onDestroy() {
        top_bannerView.destroy();
    }

    public void showBannerAd() {
        if (top_bannerView != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (!top_bannerViewShowing) {
                        top_bannerView.loadAd(new AdRequest.Builder().build());
                        top_bannerViewShowing = true;
                    }
                    if (!top_bannerView.isEnabled()) {
                        top_bannerView.setEnabled(true);
                    }
                    if (top_bannerView.getVisibility() == View.INVISIBLE) {
                        top_bannerView.setVisibility(View.VISIBLE);
                    }
                }
            });
        }
    }

    public void hideBanner() {
        if (top_bannerView != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (top_bannerView.isEnabled()) {
                        top_bannerView.setEnabled(false);
                    }
                    if (top_bannerView.getVisibility() != View.INVISIBLE) {
                        top_bannerView.setVisibility(View.INVISIBLE);
                    }
                }
            });
        }
    }

    public void showInterstitial() {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                InterstitialAd.load(activity, interstitialId, new AdRequest.Builder().build(), new InterstitialAdLoadCallback() {
                    @Override
                    public void onAdLoaded(@NonNull InterstitialAd interstitialAd) {
                        interstitialAd.show(activity);
                    }
                    @Override
                    public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                    }
                });
            }
        });
    }

    private void setupAdBannerView() {
        setupTopBannerView();
        hideBanner();
    }

    private void setupTopBannerView() {
        top_bannerView = new AdView(activity);
        top_bannerView.setAdSize(AdSize.BANNER);
        top_bannerView.setAdUnitId(top_bannerId);
        FrameLayout.LayoutParams topLayoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT, FrameLayout.LayoutParams.WRAP_CONTENT, android.view.Gravity.TOP | android.view.Gravity.CENTER_HORIZONTAL);
        top_bannerView.setBackgroundColor(Color.BLACK);
        top_bannerView.setBackgroundColor(0);
        activity.addContentView(top_bannerView, topLayoutParams);
    }
}
