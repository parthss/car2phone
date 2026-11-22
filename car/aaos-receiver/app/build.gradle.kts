plugins {
    id("com.android.application")
    id("org.jetbrains.kotlin.android")
}

android {
    namespace = "org.car2phone.receiver"
    compileSdk = 34

    defaultConfig {
        applicationId = "org.car2phone.receiver"
        minSdk = 29 // Android 10 Automotive
        targetSdk = 34
        versionCode = 1
        versionName = "0.1.0"
        externalNativeBuild {
            cmake { cppFlags += "-std=c++17" }
        }
    }

    externalNativeBuild {
        cmake { path = file("src/main/cpp/CMakeLists.txt") }
    }

    // Ship the repository's reference profiles as assets (profiles/*.ini).
    sourceSets.getByName("main").assets.srcDir("../../../profiles")

    // Car API (CarPropertyManager) is provided by the AAOS system image.
    useLibrary("android.car")

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
    kotlinOptions { jvmTarget = "17" }
}

// Deliberately no Google Mobile Services dependencies: see README.
dependencies {
    implementation("androidx.core:core-ktx:1.13.1")
}
