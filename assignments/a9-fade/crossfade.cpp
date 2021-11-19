#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <stdio.h>
#include <string.h>

using namespace atk;
using namespace atkui;
using namespace glm;

class ACrossfadeViewer : public atkui::Framework
{
public:
  ACrossfadeViewer() : atkui::Framework(atkui::Perspective) {}
  virtual ~ACrossfadeViewer() {}

  void loadMotion1(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion1_);
  }

  void loadMotion2(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion2_);
  }
Motion blend(const Motion& m1, const Motion& m2, double alpha)
   {
      Motion blend;
      blend.setFramerate(m1.getFramerate());
   
      // todo: replace the following line with your code
      double duration1 = m1.getDuration();
      double duration2 = m2.getDuration();
      double duration = duration1 * (1-alpha) + duration2 * alpha;
      double deltaT = 1/m1.getFramerate();
      for(double t = 0; t < duration; t+=deltaT){
           Pose pose1 = m1.getValue(t);
           Pose pose2 = m2.getValue(t);
           Pose newPose = Pose::Lerp(pose1, pose2, alpha);
           blend.appendKey(newPose);
      }

     // placeholder
      return blend;
   }
  void crossfade(int numBlendFrames)
  {
    assert(motion1_.getNumKeys() > 0);
    assert(motion2_.getNumKeys() > 0);
    assert(numBlendFrames > 0);
    assert(numBlendFrames <= motion1_.getNumKeys());
    assert(numBlendFrames <= motion2_.getNumKeys());
    //framerate slow down doesn't work
   motion1_.setFramerate(motion1_.getFramerate()/15.0);
    motion2_.setFramerate(motion2_.getFramerate()/15.0);
    int start1 = motion1_.getNumKeys() - numBlendFrames;
    int start2 = 0;
    //part 1.1
    /*
    for(int i = 0;i<motion1_.getNumKeys();i++){
        blend_.appendKey(motion1_.getKey(i));
    }
    for(int i = 0;i<motion2_.getNumKeys();i++){
        blend_.appendKey(motion2_.getKey(i));
    }
    */
    //part 2.2
    for(int i = 0;i<start1;i++){
        blend_.appendKey(motion1_.getKey(i));
    }

    //align keys starting with the first frame of jump
    Pose lastPoseWalk = motion1_.getKey(motion1_.getNumKeys()-1);
    Pose poseJump = motion2_.getKey(0);
 
    Transform one = Transform(quat(0, vec3(1, 0, 0)), vec3(-poseJump.rootPos.x, -poseJump.rootPos.y, -poseJump.rootPos.z));
    Transform desiredTr = Transform(lastPoseWalk.jointRots[0],lastPoseWalk.rootPos );
    Transform orig = Transform(poseJump.jointRots[0], poseJump.rootPos);
    Transform offset = desiredTr*(orig.inverse());

    //get first frame root transfrom
      Transform intermediate = orig * one;
      Transform newTr = intermediate * desiredTr;
     motion2_.getKey(0).rootPos = newTr.t();
      motion2_.getKey(0).jointRots[0] = newTr.r();
    //align the rest of the frames 
    for(int i=1;i<motion2_.getNumKeys();i++){
         Pose poseJump = motion2_.getKey(i);
          //calculate the transfrom for frame i
          Transform currTransform = Transform(poseJump.jointRots[0], poseJump.rootPos);
          Transform currOffset = offset * currTransform;
          motion2_.getKey(i).rootPos = currOffset.t();
          motion2_.getKey(i).jointRots[0] = currOffset.r();
         
    }

    double alpha = 0;
    double increment = 1.0/((double)numBlendFrames-1);
    for(int i=0;i<numBlendFrames;i++){
          blend_.appendKey(Pose::Lerp(motion1_.getKey(start1+i), motion2_.getKey(start2), alpha));
         
         /*
          for(double t = 0;t<=duration;t+=delta){
               double t1=(t/duration)*motion1_.getDuration();
               double t2=(t/duration)*motion2_.getDuration();
               Pose pose1 = moion1_.getValue(t1);
               Pose pose2 = motion2_.getValue(t2);
               Pose pose = Pose::Lerp(Pose1, Pose2, alpha);
               blend.append(pose);
          }
         */
          start2++;
          alpha+=increment;
          

    }
    for(int i = start2;i<motion2_.getNumKeys();i++){
        blend_.appendKey(motion2_.getKey(i));
    }

    
    // TODO: Your code here
  }

  void save(const std::string &filename)
  {
    BVHWriter writer;
    writer.save(filename, skeleton_, blend_);
  }

  void scene()
  {
    blend_.update(skeleton_, elapsedTime());
    drawer_.draw(skeleton_, *this);
  }

private:
  Skeleton skeleton_;
  SkeletonDrawer drawer_;
  Motion motion1_;
  Motion motion2_;
  Motion blend_;
};

std::string PruneName(const std::string &name)
{
  int idx1 = name.find_last_of("/");
  int idx2 = name.find_last_of(".");
  return name.substr(idx1 + 1, idx2 - idx1 - 1);
}

int main(int argc, char **argv)
{
  std::string motion1 = "../motions/Beta/walking.bvh";
  std::string motion2 = "../motions/Beta/jump.bvh";
  int numFrames = 10;

  try
  {
    for (int i = 0; i < argc; i++)
    {
      if (strncmp(argv[i], "-m1", 3) == 0)
        motion1 = argv[i + 1];
      else if (strncmp(argv[i], "-m2", 3) == 0)
        motion2 = argv[i + 1];
      else if (strncmp(argv[i], "-nframes", 7) == 0)
        numFrames = std::stoi(argv[i + 1]);
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "usage: crossfade -m1 <path> -m2 <path> -nframes <num frames>\n";
  }

  ACrossfadeViewer viewer;
  viewer.loadMotion1(motion1);
  viewer.loadMotion2(motion2);
  viewer.crossfade(numFrames);

  std::string saveName = "blend-" + PruneName(motion1) + PruneName(motion2);
  saveName += "-" + std::to_string(numFrames) + ".bvh";
  viewer.save(saveName);

  viewer.run();
  return 0;
}
