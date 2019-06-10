pipeline {
  agent any

  stages {
    stage('Build') {
      steps {
        checkout scm
        sh '''mkdir -p build
              cd build
              conan install ..
              cmake -DCMAKE_BUILD_TYPE=Release ../source 
              cmake --build .
           '''
      }
    }
    stage('Test') {
      steps {
        checkout scm
        sh '''cd build
              ctest -V
           '''
      }
    }
    stage('Docker.Build') {
      steps {
        sh '''docker build --tag service.example .
              docker images
           '''
      }
    }
  }
}