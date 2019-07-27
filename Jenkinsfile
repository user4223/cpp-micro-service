pipeline {
  agent any

  stages {
    stage('Build') {
      steps {
        checkout scm
        sh '''mkdir -p build
              cd build
              conan install --build=missing ..
              cmake -DCMAKE_BUILD_TYPE=Release ../source 
              cmake --build . -- -j
           '''
      }
    }
    stage('Test') {
      steps {
        checkout scm
        sh '''cd build
              ctest -V
           '''
        xunit([GoogleTest(
           deleteOutputFiles: true
          ,failIfNotNew: true
          ,pattern: '**/*.test.result.xml'
          ,skipNoTestFiles: false
          ,stopProcessingIfError: true)])
      }
    }
    stage('Docker.Build') {
      steps {
        sh '''docker build --tag front .
              docker images
           '''
      }
    }
    stage('Docker.Run') {
      steps {
        sh '''set +e
              docker stop front > /dev/null 2>&1
              docker container rm front > /dev/null 2>&1
              set -e
              docker run -d -p 127.0.0.1:6565:6565 front:latest
           '''
      }
    }
  }
}
