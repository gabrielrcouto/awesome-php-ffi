#define FFI_LIB "/System/Library/Frameworks/ApplicationServices.framework/Frameworks/SpeechSynthesis.framework/Versions/Current/SpeechSynthesis"

typedef short OSErr;

typedef short SInt16;
typedef uint32_t CFStringEncoding;
typedef struct __CFAllocator CFAllocatorRef;
typedef unsigned int FourCharCode;
typedef FourCharCode OSType;
typedef void * CFStringRef;
typedef void * CFDictionaryRef;

struct SpeechChannelRecord {
  long data[1];
};

typedef struct SpeechChannelRecord      SpeechChannelRecord;
typedef SpeechChannelRecord *           SpeechChannel;

struct VoiceSpec {
  OSType              creator;
  OSType              id;
};

typedef struct VoiceSpec                VoiceSpec;

CFStringRef CFStringCreateWithCString(CFAllocatorRef * alloc, const char *cStr, CFStringEncoding encoding);

OSErr NewSpeechChannel(VoiceSpec * voice, SpeechChannel * chan);
SInt16 SpeechBusy(void);
OSErr SpeakCFString(SpeechChannel chan, CFStringRef aString, CFDictionaryRef options);
OSErr SpeakString(char * textToBeSpoken);
