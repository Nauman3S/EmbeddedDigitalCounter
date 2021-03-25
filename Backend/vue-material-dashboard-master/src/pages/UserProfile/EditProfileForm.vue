<template>
  <form>
    <md-card>
      <md-card-header :data-background-color="dataBackgroundColor">
        <h4 class="title">Edit Profile</h4>
        <p class="category">Complete your profile</p>
      </md-card-header>

      <md-card-content>
        <div class="md-layout">
          <div class="md-layout-item md-small-size-100 md-size-33">
            <md-field>
              <label>Company</label>
              <md-input v-model="company" ></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-33">
            <md-field>
              <label>User Name</label>
              <md-input v-model="username" type="text"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-33">
            <md-field>
              <label>Email Address</label>
              <md-input v-model="emailadress" type="email"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-50">
            <md-field>
              <label>First Name</label>
              <md-input v-model="firstname" type="text"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-50">
            <md-field>
              <label>Last Name</label>
              <md-input v-model="lastname" type="text"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-100">
            <md-field>
              <label>Address</label>
              <md-input v-model="address" type="text"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-33">
            <md-field>
              <label>City</label>
              <md-input v-model="city" type="text"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-33">
            <md-field>
              <label>Country</label>
              <md-input v-model="country" type="text"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-small-size-100 md-size-33">
            <md-field>
              <label>Postal Code</label>
              <md-input v-model="code" type="number"></md-input>
            </md-field>
          </div>
          <div class="md-layout-item md-size-100">
            <md-field maxlength="5">
              <label>About Me</label>
              <md-textarea v-model="aboutme"></md-textarea>
            </md-field>
          </div>
          <div class="md-layout-item md-size-100 text-right">
            <!-- <md-button class="md-raised md-success" @click="UpdateUser">Update Profile</md-button> -->
            <button  @click="UpdateUser">Update Profile</button>
          </div>
        </div>
      </md-card-content>
    </md-card>
  </form>
</template>
<script>
const API_URL = "http://edc-backend.production.wrapdrive.tech/v1/getUser";
export default {
  name: "edit-profile-form",
  props: {
    dataBackgroundColor: {
      type: String,
      default: ""
    }
  },
  data() {
    return {
      username: null,
      company: null,
      emailadress: '0',
      lastname: null,
      firstname: null,
      address: null,
      city: null,
      country: null,
      code: null,
      aboutme:
        "Nothing special"
    };
  },
  methods:{
  UpdateUser(){
    console.log('updating')
    const requestOptions = {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ username: this.username, company:this.company,email:this.emailadress,lastname:this.lastname,firstname:this.firstname,
                           address:this.address,city:this.city,country:this.country,postalcode:this.code,aboutme:this.aboutme   
    })
  };
  fetch("http://edc-backend.production.wrapdrive.tech/v1/updateUser", requestOptions)
    .then(response => response.json())
    .then();//data => (this.postId = data.id)

  },
  },
mounted(){
    fetch(API_URL)
       fetch(API_URL)
      .then(response => response.json())
      .then(result => {
        
        this.username =''+ result['data'][0].username,
        this.emailadress = result['data'][0].email
        this.company = result['data'][0].company
        this.lastname=result['data'][0].lastname
        this.firstname=result['data'][0].firstname
        this.address=result['data'][0].address
        this.city=result['data'][0].city
        this.country=result['data'][0].country
        this.aboutme=result['data'][0].aboutme
        this.code=result['data'][0].postalcode

        //JSON.parse(result['data'])

      });
  },
  
};
</script>
<style></style>
