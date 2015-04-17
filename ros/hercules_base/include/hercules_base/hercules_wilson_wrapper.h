/**
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CLEARPATH ROBOTICS, INC. BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef HERCULES_BASE_HERCULES_WILSON_WRAPPER_H
#define HERCULES_BASE_HERCULES_WILSON_WRAPPER_H

#include "boost/type_traits/is_base_of.hpp"

namespace hercules_wilson
{
  void connect(std::string port);

  void reconnect();

  void configureLimits(double max_speed, double max_accel);

  void controlSpeed(double speed_left, double speed_right, double accel_left, double accel_right);

  template<typename T>
    struct Channel
    {
      typedef boost::shared_ptr <T> Ptr;
      typedef boost::shared_ptr<const T> ConstPtr;
      BOOST_STATIC_ASSERT_MSG(
          (boost::is_base_of<Message, T>::value),
          "T must be a descendant of Message"
      );

      static Ptr requestData(double timeout)
      {
        T *update = 0;
        while(!update)
        {
          update = T::getUpdate(timeout);
          if(!update){
            reconnect();
          }
        }
        return Ptr(update);
      }
    };

} // namespace hercules_wilson

#endif  // HERCULES_BASE_HERCULES_WILSON_WRAPPER_H
